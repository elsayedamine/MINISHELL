/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:29:54 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/29 17:25:13 by ahakki           ###   ########.fr       */
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

void	feed_str(char **n, char *s)
{
	int i;
	int q;
	int j;

	i = 0;
	j = 0;
	q = 0;
	*n = alloc(ft_strlen(s) + 1, NULL, 'M');
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && !q)
			q = s[i];
		else if ((s[i] == '"' || s[i] == '\'') && q == s[i])
			q = !q;
		else if (!q && ft_strchr(WHITE, s[i]))
			break ;
		(*n)[j++] = s[i++];
	}
	(*n)[j] = '\0';
}

int	ft_wc(t_list *node, char **n)
{
	char	*s;
	int		i;
	int		q;

	if (!node || !node->content)
		return (0);
	s = alloc(0, ft_strtrim(node->content, WHITE), 0);
	ft_init(2, &i, &q);
	while (s[i])
	{
		if ((s[i] == '"' || s[i] == '\'') && !q)
			q = s[i++];
		else if ((s[i] == '"' || s[i] == '\'') && q == s[i] && i++)
			q = !q;
		else if (!q && ft_strchr(WHITE, s[i]) && i++)
			break ;
		else
			i++;
	}
	if (!s[i])
		return (FALSE);
	return (feed_str(n, s + i), TRUE);
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
		if (is_red(c, 'r') && !tmp->next)
			return (throw_error(SYNTAX, "newline", NULL), FALSE);
		if (is_red(c, 'r') && tmp->next && (is_op(n) || is_red(n, 'r')))
			return (throw_error(SYNTAX, n, NULL), FALSE);
		if (is_par(c) && *c == ')' && tmp->next && is_red(n, 'r') && ft_wc(tmp->next->next, &n))
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
