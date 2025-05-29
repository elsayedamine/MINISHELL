/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:29:54 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/29 02:34:31 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(char *str, char r)
{
	int		len;
	char	c;

	if (r == 'r')
	{
		if (str)
		{
			c = *str;
			len = ft_strlen(str);
			if (len <= 2 && (c == '>' || c == '<'))
				return (c);
		}
		return (FALSE);
	}
	else
	{
		if (ft_strlen(str) > 2)
			return (TRUE);
		if (!is_op(str) && !is_par(str) && !is_red(str, 'r'))
			return (TRUE);
		return (FALSE);
	}
}

int	is_there_red(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (ft_strchr(WHITE, str[i]) && str[i])
		i++;
	if (ft_strchr("<>", str[i]))
		return (TRUE);
	return (FALSE);
}

int	isvalid_red(t_shell *vars)
{
	t_list	*tmp;
	char	*c;
	char	*n;
	char	**split;

	tmp = vars->args;
	while (tmp)
	{
		c = (char *)tmp->content;
		if (tmp->next)
			n = (char *)tmp->next->content;
		split = _ft_split(n, ' ');
		if (is_red(c, 'r') && !tmp->next)
			return (throw_error(SYNTAX, "newline", NULL), FALSE);
		if (is_red(c, 'r') && tmp->next && (is_op(n) || is_red(n, 'r')))
			return (throw_error(SYNTAX, *split, NULL), FALSE);
		// if (is_red(c, 'r') && tmp->next && ft_arrlen(split) != 1)
		// 	return (throw_error(SYNTAX, *(split + 1), NULL), FALSE);
		tmp = tmp->next;
	}
	return (TRUE);
}

int	nodejoin(t_shell *vars)
{
	if (ft_nodejoin(vars) == FALSE)
		return (FALSE);
	pop_spaces(vars);
	return (TRUE);
}
