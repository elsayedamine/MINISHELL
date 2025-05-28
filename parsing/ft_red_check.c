/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:29:54 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/28 14:30:19 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_red(char *str)
{
	int		len;
	char	c;

	if (str)
	{
		c = *str;
		len = ft_strlen(str);
		if (len <= 2 && (c == '>' || c == '<'))
			return (c);
	}
	return (FALSE);
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
	char	**split;

	tmp = vars->args;
	while (tmp)
	{
		c = (char *)tmp->content;
		if (tmp->next)
			n = (char *)tmp->next->content;
		// we will use count words of custom split  for n (handle it)
		split = _ft_split(n, ' ');
		if (is_red(c) && !tmp->next)
			return (throw_error(SYNTAX, "newline", NULL), FALSE);
		if (is_red(c) && tmp->next && (is_op(n) || is_red(n) || ft_arrlen(split) != 1))
			return (throw_error(SYNTAX, n, NULL), FALSE);
		
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
