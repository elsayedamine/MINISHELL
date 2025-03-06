/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:43:13 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/06 01:05:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_shell	g_vars;

int	isvalid_par(void)
{
	t_list (*tmp) = g_vars.args;
	while (tmp && tmp->content)
	{
		if (*(char *)tmp->content == '(')
			g_vars.check.fpar++;
		if (*(char *)tmp->content == ')')
			g_vars.check.lpar--;
		tmp = tmp->next;
	}
	if (g_vars.check.fpar + g_vars.check.lpar == 0)
		return (TRUE);
	return (throw_error(SYNTAX), FALSE);
}

int	is_op(char *str)
{
	int (len);
	char (c);
	if (str)
	{
		c = str[0];
		len = ft_strlen(str);
		if (len <= 2 && (c == '&' || c == '|'))
			return (TRUE);
	}
	return (FALSE);
}

int	is_par(char *str)
{
	int (len);
	char (c);
	if (str)
	{
		c = str[0];
		len = ft_strlen(str);
		if (len == 1 && (c == '(' || c == ')'))
			return (TRUE);
	}
	return (FALSE);
}

int	isvalid_quotes(void)
{
	t_list (*tmp) = g_vars.args;
	int (len);
	while (tmp)
	{
		if (tmp->content)
		{
			len = ft_strlen((char *)tmp->content);
			if (((char *)tmp->content)[0] == '"' && \
			(((char *)tmp->content)[len - 1] != '"' || len == 1))
				return (throw_error(SYNTAX), FALSE);
		}
		if (tmp->content)
		{
			len = ft_strlen((char *)tmp->content);
			if (((char *)tmp->content)[0] == '\'' && \
			(((char *)tmp->content)[len - 1] != '\'' || len == 1))
				return (throw_error(SYNTAX), FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
