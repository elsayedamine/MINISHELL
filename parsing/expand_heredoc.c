/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:31:56 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 22:32:05 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_heredoc_line(t_shell *vars, char **str)
{
	char	*s;
	int		i;
	int		q;
	char	*new;
	t_list	*lst;

	s = *str;
	ft_init(2, &i, &q);
	lst = NULL;
	while (s && s[i])
	{
		if (s[i] == '$')
			i += extract_var_value(vars, &lst, &s[i], 0);
		else
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&s[i++], 1)));
	}
	free(*str);
	new = ft_lst2str(lst);
	return (ft_lstclear(&lst, free), new);
}
