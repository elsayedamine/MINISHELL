/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:06:14 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/24 21:08:26 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(char **env, char *key, char *nv, t_shell *vars)
{
	int		i;

	i = 0;
	(void)vars;
	if (!key || !nv)
		return ;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free(env[i]);
			env[i] = ft_strjoin(key, nv);
			return ;
		}
		i++;
	}
}

int	change_dir(char *target, char **envp, t_shell *vars)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = (char *)alloc(0, getcwd(NULL, 0), 0);
	if (chdir(target) == -1)
		return (printfd(2, "cd: %s: %s\n", strerror(errno), target), FALSE);
	pwd = (char *)alloc(0, getcwd(NULL, 0), 0);
	update_env(envp, "PWD=", pwd, vars);
	if (oldpwd)
		update_env(envp, "OLDPWD=", oldpwd, vars);
	else
		update_env(envp, "OLDPWD=", pwd, vars);
	return (TRUE);
}

int	cd(int ac, char **av, t_shell *vars)
{
	if (ac == 1)
		return (printfd(2, \
			"%s: cd: only relative or absolute path supported\n", M), 1);
	if (ac > 2)
		return (printfd(2, "cd: too many arguments\n"), EXIT_FAILURE);
	if (!change_dir(av[1], vars->envp, vars))
		return (EXIT_FAILURE);
	vars->env = ft_arr2list(vars->envp);
	vars->pwd = (char *)alloc(0, ft_strdup(get_env("PWD", vars)), 0);
	return (EXIT_SUCCESS);
}
