/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:35:00 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/25 00:29:48 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_arrdup(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	if (!arr)
		return (NULL);
	dup = (char **)alloc(sizeof(char *) * (ft_arrlen(arr) + 1), NULL, 'M');
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = (char *)alloc(0, ft_strdup(arr[i]), 0);
		if (!dup[i])
		{
			// clear();
			return (ft_free("2", dup), NULL);		
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
