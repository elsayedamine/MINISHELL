/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:21:38 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/16 19:30:28 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_clear(t_lst **lst)
{
	t_lst	*store;

	if (lst && *lst)
	{
		while (*lst)
		{
			store = (*lst)->next;
			free(*lst);
			*lst = store;
		}
		*lst = NULL;
	}
}
