/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/12 11:24:14 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset(int ac, char **av, **env)
{
	char	*cwd;

	if (ac == 1)
		printfd(2, "unset: not enough arguments\n");
	if (ft_strncmp(env[i], key, ft_strlen(key)))
		return (update_variable(&env[i], new_value, key));
}