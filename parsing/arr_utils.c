/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 02:15:03 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/25 02:16:49 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_arr2list(char **arr)
{
	t_list	*list;
	t_list	*new;

	if (!arr)
		return (NULL);
	list = NULL;
	while (*arr)
	{
		new = alloc(0, ft_lstnew(alloc(0, ft_strdup(*arr), 0)), 0);
		if (!new)
		{
			clear(1);
			return (ft_lstclear(&list, free), NULL);
		}
		ft_lstadd_back(&list, new);
		arr++;
	}
	return (list);
}

char	**ft_arrdup(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	if (!arr)
		return (NULL);
	dup = (char **)alloc(sizeof(char *) * (ft_arrlen(arr) + 1), NULL, 'M');
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = (char *)alloc(0, ft_strdup(arr[i]), 0);
		if (!dup[i])
		{
			clear(1);
			return (ft_free("2", dup), NULL);		
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char	**ft_list2arr(t_list *lst)
{
	char	**arr;
	int		i;
	int		words;

	if (!lst)
		return (NULL);
	words = ft_lstsize(lst);
	arr = (char **)alloc((words + 1) * sizeof(char *), NULL, 'M');
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words && lst)
	{
		arr[i] = alloc(0, ft_strdup(lst->content), 0);
		if (!arr[i++])
			clear(1);
		lst = lst->next;
	}
	arr[words] = NULL;
	return (arr);
}
