/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:33:33 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/03 20:08:39 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_list2arr(t_list *lst)
{
	char	**arr;

	int (i), (words);
	if (!lst)
		return (NULL);
	words = ft_lstsize(lst);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words && lst)
	{
		arr[i] = ft_strdup(lst->content);
		if (!arr[i++])
			return (ft_free("2", arr), NULL);
		lst = lst->next;
	}
	arr[words] = NULL;
	i = 0;
	return (arr);
}
