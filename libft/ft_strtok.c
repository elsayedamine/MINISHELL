/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:16:51 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/21 16:57:38 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, char const *delim)
{
	static char *next_token;
	char		*start;
	int			len;

	if (str)
		next_token = str;
	if (!next_token || !*next_token)
		return (NULL);
	if (ft_strchr(delim, *next_token))
		return (ft_strndup(next_token++, 1));
	len = 0;
	start = next_token;
	while (*next_token && !ft_strchr(delim, *next_token))
	{
		len++;
		next_token++;
	}
	return (ft_strndup(start, len));
}
