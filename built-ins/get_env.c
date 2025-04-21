/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:47:01 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/21 10:56:54 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *k, t_shell *vars)
{
	int		i;
	char	**env;

	i = 0;
	if (!vars || !vars->envp || !k)
		return (NULL);
	env = vars->envp;
	while (env[i])
	{
		if (ft_strnstr(env[i], k, ft_strlen(k)) == env[i] \
			&& env[i][ft_strlen(k)] == '=')
			return (env[i] + ft_strlen(k) + 1);
		i++;
	}
	return (NULL);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_shell vars;
// 	vars.envp = ft_arrdup(envp);

// 	printf("%s\n", get_env(av[1], &vars));
// 	return (0);
// }
