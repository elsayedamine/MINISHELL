/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:06:14 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/30 16:22:37 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_env(char **env, char *key, char *new_value)
{
	int	i;

	i = 0;
	if (!key || !new_value)
		return ;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free(env[i]);
			env[i] = ft_strjoin(key, new_value);
			return ;
		}
		i++;
	}
}

int	change_dir(char *target, char **envp)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(target) == -1)
		return (printfd(2, "cd: %s: %s\n", strerror(errno), target));
	pwd = getcwd(NULL, 0);
	update_env(envp, "PWD=", pwd);
	update_env(envp, "OLDPWD=", oldpwd);
	return (free(pwd), free(oldpwd), TRUE);
}

int	cd(int ac, char **av, t_shell *vars)
{
	if (ac == 1)
		return (printfd(2, \
			"%s: cd: only relative or absolute path supported\n", M));
	if (ac > 2)
		return (printfd(2, "cd: too many arguments\n"), 127);
	change_dir(av[1], vars->envp);
	ft_lstclear(&vars->env, free);
	vars->env = ft_arr2list(vars->envp);
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
