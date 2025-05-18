/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:30:19 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/18 03:01:48 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_nodejoin(t_shell *vars)
{
	char *(new_content), *(tmp_content);
	t_list *(to_delete), *(tmp) = vars->args;
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP, NULL, NULL), FALSE);
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
		return (throw_error(OP, NULL, NULL), FALSE);
	return (TRUE);
}

int	isvalid_syntax(t_shell *vars)
{
	t_list	*tmp;
	char	*c;
	char	*n;

	tmp = vars->args;
	while (tmp)
	{
		c = (char *)tmp->content;
		if (tmp->next)
			n = (char *)tmp->next->content;
		if (is_par(c) && tmp->next && is_par(n) && *c != *n)
			return (throw_error(OP, NULL, NULL), FALSE);
		if (!is_par(c) && !is_op(c) && tmp->next && is_par(n) && *n == '(')
			return (throw_error(OP, NULL, NULL), FALSE);
		if (!is_par(c) && is_op(c) && tmp->next && is_par(n) && *n == ')')
			return (throw_error(OP, NULL, NULL), FALSE);
		if (is_par(c) && *c == '(' && tmp->next && is_op(n) && *n != '<')
			return (throw_error(OP, NULL, NULL), FALSE);
		if (is_par(c) && *c == ')' && tmp->next && !is_op(n) && !is_par(n))
			return (throw_error(OP, NULL, NULL), FALSE);
		tmp = tmp->next;
	}
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

int	ft_check(t_shell *vars)
{
	if (isvalid_quotes(vars) == FALSE)
		return (FALSE);
	if (isvalid_op(vars) == FALSE)
		return (FALSE);
	if (isvalid_par(vars) == FALSE)
		return (FALSE);
	if (ft_nodejoin(vars) == FALSE)
		return (FALSE);
	pop_spaces(vars);
	if (isvalid_syntax(vars) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	throw_error(int error, char *file, int *exitt)
{
	if (error == ENOENT)
		printfd(2, "%s: %s\n", file, strerror(ENOENT));
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	if (error == CMD_NOT_FOUND)
	{
		printfd(2, "Command not found : %s\n", file);
		return (*exitt = 127, (void)file);
	}
	if (error == DIRECT)
		printfd(2, "Cannot open current working directory\n");
}
