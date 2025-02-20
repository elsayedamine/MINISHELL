/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addfront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 19:20:07 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/16 19:30:12 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_addfront(t_lst **lst, t_lst *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}
