/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:35:00 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/08 16:43:16 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_arrdup(char **arr)
{
	char	**dup;
	int		i;

	i = 0;
	if (!arr)
		return (NULL);
	dup = (char **)malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		dup[i] = ft_strdup(arr[i]);
		if (!dup[i])
			return (ft_free("2", dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
