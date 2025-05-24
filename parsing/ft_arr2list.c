/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr2list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:00:55 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/25 00:29:41 by aelsayed         ###   ########.fr       */
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
			// clear();
			return (ft_lstclear(&list, free), NULL);
		}
		ft_lstadd_back(&list, new);
		arr++;
	}
	return (list);
}
