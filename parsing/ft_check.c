/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:30:19 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/08 09:31:28 by aelsayed         ###   ########.fr       */
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
		if (!is_par(c) && !is_op(c) && !ft_iswhitespace(c) \
			&& tmp->next && is_par(n) && *n == '(')
			return (throw_error(OP), FALSE);
		if (!is_par(c) && is_op(c) && tmp->next && is_par(n) && *n == ')')
			return (throw_error(OP), FALSE);
		if (is_par(c) && *c == '(' && tmp->next && is_op(n) && *n != '<')
			return (throw_error(OP), FALSE);
		if (is_par(c) && *c == ')' && tmp->next && !is_op(n) \
			&& !is_par(n) && !ft_iswhitespace(n))
			return (printf("2\n"), throw_error(OP), FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

int	ft_check(t_shell *vars)
{
	if (isvalid_quotes(vars) == FALSE)
		return (FALSE);
	if (isvalid_op(vars) == FALSE)
		return (FALSE);
	if (isvalid_syntax(vars) == FALSE)
		return (FALSE);
	if (isvalid_par(vars) == FALSE)
		return (FALSE);
	if (ft_nodejoin(vars) == FALSE)
		return (FALSE);
	return (TRUE);
}
