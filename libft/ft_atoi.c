/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:26:09 by aelsayed          #+#    #+#             */
/*   Updated: 2024/11/04 16:10:13 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(char const *str)
{
	unsigned int	i;
	int				sign;
	long			n;
	long			min;
	long			max;

	i = 0;
	sign = 1;
	n = 0;
	min = -9223372036854775807 - 1;
	max = 9223372036854775807;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (sign == 1 && (n > (max - (str[i] - '0')) / 10))
			return (-1);
		else if (sign == -1 && (n < (min + (str[i] - '0')) / 10))
			return (0);
		n = n * 10 + (str[i++] - '0');
	}
	return (n * sign);
}
