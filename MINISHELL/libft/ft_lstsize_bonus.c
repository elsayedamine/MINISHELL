/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:14:18 by aelsayed          #+#    #+#             */
/*   Updated: 2024/10/29 22:05:41 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	node_nbr;

	node_nbr = 0;
	while (lst != NULL)
	{
		node_nbr++;
		lst = lst->next;
	}
	return (node_nbr);
}
