/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr2list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:00:55 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/20 17:03:01 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_arr2list(char **arr)
{
	t_list	*list;
	t_list	*new;

	if (!arr)
		return (NULL);
	list = NULL;
	while (*arr)
	{
		new = ft_lstnew(ft_strdup(*arr));
		if (!new)
			return (ft_lstclear(&list, free), NULL);
		ft_lstadd_back(&list, new);
		arr++;
	}
	return (list);
}
