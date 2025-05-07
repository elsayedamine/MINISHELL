/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:58:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/07 19:07:18 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quote(char *quote, t_list **chunk, char *c)
{
	if (!*quote)
		*quote = *c;
	else if (*quote == *c)
		*quote = 0;
	else
		ft_lstadd_back(chunk, ft_lstnew(ft_strdup(c)));
}

char	**split_list(t_list *lst, char sep)
{
	t_list	*new;
	t_list	*chunk;
	char	**arr;
	char	quote;

	quote = 0;
	new = NULL;
	chunk = NULL;
	while (lst)
	{
		if (!lst->type && ft_strchr("'\"", *(char *)lst->content))
			handle_quote(&quote, &chunk, lst->content);
		else if (!quote && !lst->type && *(char *)lst->content == sep)
		{
			ft_lstadd_back(&new, ft_lstnew(ft_lst2str(chunk)));
			ft_lstclear(&chunk, free);
		}
		else
			ft_lstadd_back(&chunk, ft_lstnew(ft_strdup((char *)lst->content)));
		lst = lst->next;
	}
	if (chunk)
		ft_lstadd_back(&new, ft_lstnew(ft_lst2str(chunk)));
	arr = ft_list2arr(new);
	return (ft_lstclear(&chunk, free), ft_lstclear(&new, free), arr);
}
