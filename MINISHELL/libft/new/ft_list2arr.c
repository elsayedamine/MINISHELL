/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list2arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:33:33 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/13 03:34:04 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_list2arr(t_list *tmp_arr)
{
	char	**arr;

	int (i), (words);
	if (!tmp_arr)
		return (NULL);
	words = ft_lstsize(tmp_arr);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words && tmp_arr)
	{
		arr[i] = ft_strdup(tmp_arr->content);
		if (!arr[i++])
			return (ft_free("2", arr), NULL);
		tmp_arr = tmp_arr->next;
	}
	arr[words] = NULL;
	i = 0;
	return (arr);
}
