/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:23:41 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/08 17:14:11 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putarr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ((void)printfd(1, "Null array\n"));
	while (arr[i])
	{
		printfd(1, "words %d : %s\n", i, arr[i]);
		i++;
	}
}
