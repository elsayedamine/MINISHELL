/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/07 03:03:11 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_vars;

void	throw_error(int error)
{
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	g_vars.exit = 127;
}

int	ft_nodejoin(void)
{
	t_list (*to_delete), (*tmp) = g_vars.args;
	char (*new_content);
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	while (tmp && tmp->next)
	{
		if (!is_op((char *)tmp->content) && !is_op((char *)tmp->next->content) && \
		!is_par((char *)tmp->content) && !is_par((char *)tmp->next->content))
		{
			new_content = ft_strjoin((char *)tmp->content, (char *)tmp->next->content);
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

int	fill_args(void)
{
	char (*token);
	if (!g_vars.cmd || !*(g_vars.cmd))
		return (0);
	token = ft_strtok(g_vars.cmd, "'\"()|&><");
	while (token)
	{
		ft_lstadd_back(&g_vars.args, ft_lstnew(token));
		token = ft_strtok(NULL, "'\"()|&><");
	}
	if (!ft_check())
		return (FALSE);
	g_vars.tmp = g_vars.args;
	return (ft_lstiter(g_vars.tmp, printf), 0);
}

// int	isvalid_around_par(void)
// {
// 	t_list (*tmp) = g_vars.args;
// 	while (tmp && tmp->next)
// 	{
// 		if (*(char *)tmp->next->content == '(' && *(char *)tmp->content)
// 	}
// }

//we shoud implement the fct that parses the peripheric of the paranthesis
// () )(  &(&)  ()|  ()a : nooooo
