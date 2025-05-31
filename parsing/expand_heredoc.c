/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:31:56 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 03:25:53 by aelsayed         ###   ########.fr       */
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

void	clean_heredoc(t_shell *vars)
{
	t_list	*tmp;
	t_redir	*r;

	tmp = vars->hd;
	while (tmp)
	{
		r = (t_redir *)tmp->content;
		unlink(r->target);
		tmp = tmp->next;
	}
}
