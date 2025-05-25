/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:58:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/25 13:41:40 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	append(t_list **s, char c, int type)
{
	t_list	*new;
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	new = alloc(0, ft_lstnew(alloc(0, ft_strndup(tmp, 1), 0)), 0);
	new->type = type;
	ft_lstadd_back(s, new);
	return (1);
}

void	handle_quote(char *quote, t_list **chunk, char *c, t_list *n)
{
	if (!*quote)
		*quote = *c;
	else if (*quote == *c && ((n && *(char *)(*n).content == ' ' ) || !n))
	{
		*quote = 0;
		ft_lstadd_back(chunk, ft_lstnew(ft_strdup("\0")));
	}
	else if (*quote == *c)
		*quote = 0;
	else
		ft_lstadd_back(chunk, ft_lstnew(ft_strdup(c)));
}

void	split_space(t_list **chunk, t_list **new, t_list **lst, char sep)
{
	if (chunk && *chunk)
	{
		ft_lstadd_back(new, ft_lstnew(ft_lst2str(*chunk)));
		ft_lstclear(chunk, free);
	}
	while ((*lst)->next && *(char *)(*lst)->next->content == sep)
		(*lst) = (*lst)->next;
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
		if (lst->type != 1 && ft_strchr("'\"", *(char *)lst->content))
			handle_quote(&quote, &chunk, lst->content, lst->next);
		else if (!quote && *(char *)lst->content == sep)
			split_space(&chunk, &new, &lst, sep);
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

	new = create_list(lst, sep);
	arr = ft_list2arr(new);
	return (ft_lstclear(&new, free), arr);
}
