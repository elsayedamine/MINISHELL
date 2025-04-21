/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isvalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:43:13 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/21 11:51:28 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_op(char *str)
{
	int (len);
	char (c);
	if (str)
	{
		c = str[0];
		len = ft_strlen(str);
		if (len <= 2 && (c == '&' || c == '|' || c == '>' || c == '<'))
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

int	isvalid_par(t_shell *vars)
{
	char	c;

	vars->tmp = vars->args;
	while (vars->tmp && vars->tmp->content)
	{
		c = *(char *)vars->tmp->content;
		if (c == '(')
		{
			vars->check.par++;
			vars->check.lpar = '(';
			if (vars->check.fpar == 0)
				vars->check.fpar = '(';
		}
		if (c == ')')
		{
			vars->check.par--;
			vars->check.lpar = ')';
			if (vars->check.fpar == 0)
				return (throw_error(SYNTAX), FALSE);
		}
		vars->tmp = vars->tmp->next;
	}
	if (!vars->check.par)
		return (TRUE);
	return (throw_error(SYNTAX), FALSE);
}

int	isvalid_quotes(t_shell *vars)
{
	t_list	*tmp;
	int		len;

	tmp = vars->args;
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

int	isvalid_op(t_shell *vars)
{
	t_list	*tmp;
	int		len;

	tmp = vars->args;
	while (tmp)
	{
		if (tmp->content)
		{
			len = ft_strlen((char *)tmp->content);
			if (len == 1 && ((char *)tmp->content)[0] == '&')
				return (throw_error(OP), FALSE);
			if (is_op((char *)tmp->content) && tmp->next && \
				is_op((char *)tmp->next->content))
				return (throw_error(OP), FALSE);
			if (is_op((char *)tmp->content) && tmp->next && \
				ft_iswhitespace((char *)tmp->next->content) && \
					((tmp->next->next && is_op((char *)tmp->next->next->content
						)) || !(tmp->next->next)))
				return (throw_error(OP), FALSE);
			if (is_op((char *)tmp->content) && !tmp->next)
				return (throw_error(OP), FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}
