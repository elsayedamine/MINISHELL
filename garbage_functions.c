/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:23:41 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/11 23:42:22 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_array(char **arr)
{
	int (i) = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("words %d : %s\n", i, arr[i]);
		i++;
	}
}
