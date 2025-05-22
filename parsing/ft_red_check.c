/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:29:54 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/22 02:37:15 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(char *str)
{
	int (len);
	char (c);
	if (str)
	{
		c = str[0];
		len = ft_strlen(str);
		if (len <= 2 && (c == '>' || c == '<'))
			return (c);
	}
	return (FALSE);
}

int	is_word(char *str)
{
	if (ft_strlen(str) > 2)
		return (TRUE);
	if (!is_op(str) && !is_par(str) && !is_red(str))
		return (TRUE);
	return (FALSE);
}

int	isvalid_red(t_shell *vars)
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
		if (is_red(c) && !tmp->next)
			return (throw_error(PARSE_REDIR, "newline", NULL), FALSE);
		if (is_red(c) && tmp->next && is_op(n))
			return (throw_error(PARSE_REDIR, n, NULL), FALSE);
		if (is_red(c) && tmp->next && is_red(n))
			return (throw_error(PARSE_REDIR, c, NULL), FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

int	ft_check_red(t_shell *vars)
{
	pop_spaces(vars);
	if (isvalid_red(vars) == FALSE)
		return (FALSE);
	return (TRUE);
}
