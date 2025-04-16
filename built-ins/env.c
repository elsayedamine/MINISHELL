/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:38:48 by sayed             #+#    #+#             */
/*   Updated: 2025/04/16 12:50:29 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars; 

int	env(int ac, char **av)
{
	int	i;

	i = 0;
	(void)av;
	if (ac != 1)
		return (printfd(2, "env: No options or arguments are allowed!\n"), TRUE);
	while (g_vars.envp && g_vars.envp[i])
	{
		if (ft_strchr(av[i], '='))
			printf("%s\n", av[i]);
		i++;
	}
	return (TRUE);
}
