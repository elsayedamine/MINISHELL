/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:58:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/07 21:09:37 by aelsayed         ###   ########.fr       */
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

t_list	*create_list(t_list *lst, char sep)
{
	char	quote;
	t_list	*new;
	t_list	*chunk;

	quote = 0;
	new = NULL;
	chunk = NULL;
	while (lst)
	{
		if (!lst->type && ft_strchr("'\"", *(char *)lst->content))
			handle_quote(&quote, &chunk, lst->content);
		else if (!quote && *(char *)lst->content == sep && chunk)
		{
			ft_lstadd_back(&new, ft_lstnew(ft_lst2str(chunk)));
			ft_lstclear(&chunk, free);
			while (lst->next && *(char *)lst->next->content == sep)
				lst = lst->next;
		}
		else
			ft_lstadd_back(&chunk, ft_lstnew(ft_strdup((char *)lst->content)));
		lst = lst->next;
	}
	if (chunk)
		ft_lstadd_back(&new, ft_lstnew(ft_lst2str(chunk)));
	return (ft_lstclear(&chunk, free), new);
}

char	**split_list(t_list *lst, char sep)
{
	char	**arr;
	t_list	*new;
	// t_list	*wildcard;

	new = create_list(lst, sep);
	
	arr = ft_list2arr(new);
	return (ft_lstclear(&new, free), arr);
}
