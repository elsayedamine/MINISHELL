/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:22:36 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/19 18:19:36 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// function that expects only the address of an integer or a character
void	ft_init(char *format, ...)
{
	va_list	args;
	int		i;
	int		*ptr;
	char	*str;

	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == 'i')
		{
			ptr = va_arg(args, int *);
			*ptr = 0;
			i++;
		}
		else if (format[i] == 'c')
		{
			str = va_arg(args, char *);
			*str = 0;
			i++;
		}
		i++;
	}
	va_end(args);
}
