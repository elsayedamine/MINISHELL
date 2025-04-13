/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:21:56 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/13 20:35:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	env(int ac, char **av)
{
	if (ac != 1)
		return (printfd(2, "No options or arguments are allowed\n"), FALSE);
}
