/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/07 18:21:43 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

void	throw_error(int error)
{
	if (g_vars.exit != 0)
		return ;
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	if (error == CMD_NOT_FOUND)
		printfd(2, "Command not found : %s\n", g_vars.cmd_not_found);
	g_vars.exit = 127;
}

int	ft_nodejoin(t_shell *vars)
{
	char *(new_content), *(tmp_content);
	t_list *(to_delete), *(tmp) = vars->args;
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	while (tmp && tmp->next)
	{
		tmp_content = (char *)tmp->content;
		if (!is_op(tmp_content) && !is_op((char *)tmp->next->content) && \
			!is_par(tmp_content) && !is_par((char *)tmp->next->content))
		{
			new_content = ft_strjoin(tmp_content, (char *)tmp->next->content);
			if (!new_content)
				return (FALSE);
			free(tmp->content);
			tmp->content = new_content;
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(to_delete, free);
		}
		else
			tmp = tmp->next;
	}
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	return (TRUE);
}

void	split_cmds_args(t_shell *vars)
{
	int	i;

	vars->tmp = vars->args;
	while (vars->tmp)
	{
		vars->tmp->arr = _ft_split(vars->tmp->content, ' ');
		if (!vars->tmp->arr)
			return ;
		i = 0;
		while (vars->tmp->arr[i])
		{
			vars->tmp->arr[i] = removequotes(vars->tmp->arr[i]);
			i++;
		}
		vars->tmp = vars->tmp->next;
	}
}

int	fill_args(t_shell *vars)
{
	char	*token;

	if (!vars->cmd || !*(vars->cmd) || ft_iswhitespace(vars->cmd))
		return (FALSE);
	token = ft_strtok(vars->cmd, "'\"()|&><");
	while (token)
	{
		vars->args = ft_lstnew(NULL);
		ft_lstadd_back(&vars->args, ft_lstnew(token));
		vars->args->arr = NULL;
		token = ft_strtok(NULL, "'\"()|&><");
	}
	if (!ft_check(vars))
		return (FALSE);
	split_cmds_args(vars);
	return (TRUE);
}
