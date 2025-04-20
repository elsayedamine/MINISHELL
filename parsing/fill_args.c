/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/20 18:37:18 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;
void	reconfigure(t_list *lst);

void	throw_error(int error)
{
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

void	pop_spaces(t_shell *vars)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*next;
	t_list	*node;

	tmp = vars->args;
	new = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (ft_iswhitespace(tmp->content) == FALSE)
		{
			node = ft_lstnew(ft_strdup(tmp->content));
			node->arr = ft_arrdup(tmp->arr);
			ft_lstadd_back(&new, node);
		}
		ft_free("12", tmp->content, tmp->arr);
		free(tmp);
		tmp = next;
	}
	vars->args = new;
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

int	is_delim(char *s)
{
	return ((s[0] == '&' && s[1] == '&') || \
		(s[0] == '|' && s[1] == '|') || (s[0] == '|'));
}

int	is_closed_here(char c, int *quote, int *depth)
{
	if (*quote)
	{
		if (c == *quote)
			*quote = 0;
	}
	else
	{
		if (c == '\'' || c == '"')
			*quote = c;
		else if (c == '(')
			(*depth)++;
		else if (c == ')' && *depth > 0)
			(*depth)--;
	}
	return (*quote == 0 && *depth == 0);
}

// t_list	*split_with_operators(char *cmd)
// {
// 	t_list	*new;
// 	int		i = 0;
// 	int		start = 0;
// 	int		depth = 0;
// 	int		quote = 0;
// 	int		split_occurred;

// 	new = NULL;
// 	if (!cmd)
// 		return (NULL);
// 	// ft_init(4, &i, &start, &depth, &quote);
// 	split_occurred = 0;
// 	if (!ft_strstr(cmd, "&&") && !ft_strstr(cmd, "||") && !ft_strstr(cmd, "|"))
// 		return NULL;
// 	while (cmd[i])
// 	{
// 		is_closed_here(cmd[i], &quote, &depth);
// 		if (is_delim(&cmd[i]) && !quote && !depth)
// 		{
// 			if (i > start)
// 			{
// 				ft_lstadd_back(&new, ft_lstnew(ft_strndup(&cmd[start], i - start)));
// 				split_occurred = 1;
// 			}
// 			ft_lstadd_back(&new, ft_lstnew(ft_strndup(&cmd[i], 2)));
// 			i += 2;
// 			start = i;
// 		}
// 		else
// 			i++;
// 	}
// 	if (i > start)
// 	{
// 		ft_lstadd_back(&new, ft_lstnew(ft_strdup(&cmd[start])));
// 		split_occurred = 1;
// 	}
// 	if (!split_occurred)
// 	{
// 		ft_lstclear(&new, free);
// 		return (NULL);
// 	}
// 	return (new);
// }
t_list	*split_with_operators(char *cmd)
{
	t_list	*new = NULL;
	int		i = 0, start = 0;
	int		quote = 0, depth = 0;
	int		has_split = 0;

	if (!cmd)
		return (NULL);

	while (cmd[i])
	{
		is_closed_here(cmd[i], &quote, &depth);
		if (!quote && !depth && is_delim(&cmd[i]))
		{
			if (i != start)
				ft_lstadd_back(&new, ft_lstnew(ft_strndup(&cmd[start], i - start)));

			ft_lstadd_back(&new, ft_lstnew(ft_strndup(&cmd[i], (cmd[i + 1] == cmd[i]) ? 2 : 1)));

			i += (cmd[i + 1] == cmd[i]) ? 2 : 1;
			start = i;
			has_split = 1;
		}
		else
			i++;
	}
	if (start != i) // fix: allow adding tail even if start == 0
		ft_lstadd_back(&new, ft_lstnew(ft_strndup(&cmd[start], i - start)));

	if (!has_split)
	{
		ft_lstclear(&new, free);
		return (NULL);
	}
	return (new);
}


int	fill_args(t_shell *vars)
{
	char	*token;

	if (!vars->cmd || !*(vars->cmd) || ft_iswhitespace(vars->cmd))
		return (FALSE);
	token = ft_strtok(vars->cmd, "'\"()|&");
	vars->args = NULL;
	while (token)
	{
		ft_lstadd_back(&vars->args, ft_lstnew(token));
		vars->args->arr = NULL;
		token = ft_strtok(NULL, "'\"()|&");
	}
	pop_spaces(vars);
	if (!ft_check(vars))
		return (FALSE);
	split_cmds_args(vars);
	// ft_lstclear(&vars->args, free);
	// vars->args = split_with_operators(vars->cmd);
	ft_lstiter(vars->args, printf);
	// split_with_operators(vars->args->child.);
	// reconfigure(vars->args);
	return (TRUE);
}

void	reconfigure(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	if (!lst)
		return ;
	while (tmp)
	{
		tmp->child = split_with_operators(tmp->content);
		if (tmp->child && ft_lstsize(tmp->child) > 1)
			reconfigure(tmp->child);
		tmp = tmp->next;
	}
}
 