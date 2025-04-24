/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:30:19 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/24 18:39:59 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			return (throw_error(OP), FALSE);
		if (!is_par(c) && !is_op(c) && tmp->next && is_par(n) && *n == '(')
			return (throw_error(OP), FALSE);
		if (!is_par(c) && is_op(c) && tmp->next && is_par(n) && *n == ')')
			return (throw_error(OP), FALSE);
		if (is_par(c) && *c == '(' && tmp->next && is_op(n) && *n != '<')
			return (throw_error(OP), FALSE);
		if (is_par(c) && *c == ')' && tmp->next && !is_op(n) && !is_par(n))
			return (throw_error(OP), FALSE);
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
