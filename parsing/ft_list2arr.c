/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:33:33 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/25 00:29:50 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			clear(0);
		lst = lst->next;
	}
	arr[words] = NULL;
	return (arr);
}
