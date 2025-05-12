/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:06:14 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/11 18:17:12 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(char **env, char *key, char *nv, t_shell *vars)
{
	int		i;
	char	*arr[2];

	i = 0;
	if (!key || !nv)
		return ;
	arr[0] = "export";
	arr[1] = ft_strjoin(key, nv);
	if (!ft_strcmp(key, "OLDPWD="))
		return (export(2, arr, vars), free(arr[1]));
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

	oldpwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
		return (printfd(2, "cd: %s: %s\n", strerror(errno), target));
	pwd = getcwd(NULL, 0);
	update_env(envp, "PWD=", pwd, vars);
	update_env(envp, "OLDPWD=", oldpwd, vars);
	return (free(pwd), free(oldpwd), TRUE);
}

int	cd(int ac, char **av, t_shell *vars)
{
	if (ac == 1)
		return (printfd(2, \
			"%s: cd: only relative or absolute path supported\n", M));
	if (ac > 2)
		return (printfd(2, "cd: too many arguments\n"), 127);
	change_dir(av[1], vars->envp, vars);
	ft_lstclear(&vars->env, free);
	vars->env = ft_arr2list(vars->envp);
	ft_free("1", vars->pwd);
	vars->pwd = ft_strdup(get_env("PWD", vars));
	return (TRUE);
}

// int main(int ac, char **av, char **env)
// {
// 	char	**envp;
// 	char	*a, *b;

// 	envp = ft_arrdup(env);
// 	a = getcwd(NULL, 0);
// 	printf("%s\n", a);
// 	cd(ac, av, envp);
// 	b = getcwd(NULL, 0);
// 	printf("%s\n", b);
// 	ft_free("11", a, b);
// 	return (0);
// }
