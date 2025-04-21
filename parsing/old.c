/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:32:51 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/21 11:02:38 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_delim(char *s)
{
	return ((s[0] == '&' && s[1] == '&') || \
		(s[0] == '|' && s[1] == '|') || (s[0] == '|' && s[1] != '|'));
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

void	split_with_operators(t_shell *vars)
{
	t_list	*new;
	int		i;
	int		start;
	int		depth;
	int		quote;

	ft_init(4, &i, &start, &depth, &quote);
	while (vars->cmd[i])
	{
		is_closed_here(vars->cmd[i], &quote, &depth);
		if (is_delim(&vars->cmd[i]) && !quote && !depth)
		{
			if (i > start)
				ft_lstadd_back(&new, \
						ft_lstnew(ft_strndup(&vars->cmd[start], i - start)));
			ft_lstadd_back(&new, ft_lstnew(ft_strndup(&vars->cmd[i], 2)));
			i += 2;
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(&vars->cmd[start])));
}
