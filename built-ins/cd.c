/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:06:14 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/16 12:31:29 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	update_env(char **env, char *key, char* new_value)
{
	int i;

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

int	cd2(char **av, char **env, char *oldpwd)
{
	char	*dir;

	dir = av[1];
	if (!ft_strcmp(dir, "-"))
	{
		//-------------//
	}
	else if (dir[0] == '-')
		return (free(oldpwd), \
			printfd(2, "cd: %c%c: invalid option\n", dir[0], dir[1]), 0);
	else if(chdir(dir) == -1)
	{
		printfd(2, "cd: %s: No such file or directory\n", dir);
		return (free(oldpwd), FALSE);
	}
	return (TRUE);
}

int	cd3(char **av, char **env, char *oldpwd)
{
	char	*c;

	c = av[2];
	if (!ft_strcmp(av[1], "--") && chdir(av[2]) == -1)
		return (free(oldpwd), \
			printfd(2, "cd: %s: No such file or directory\n", c), 0);
	else if (!ft_strcmp(av[1], "-") || av[1][0] != '-')
		return (free(oldpwd), printfd(2, "cd: too many arguments\n"), 0);
	else if (av[1][0] == '-' && ft_strcmp(av[1], "--"))
		return (free(oldpwd), \
			printfd(2, "cd: %c%c: invalid option\n", c[0], c[1]), 0);
	return (TRUE);
}

int	cd1(char **av, char **env, char *oldpwd)
{
	char	*home;
	
	home = getenv("HOME");
	if (!home || chdir(home) == -1)
	{
		printfd(2, "cd: HOME not set or invalid\n");
		return (free(oldpwd), FALSE);
	}
	return (TRUE);
}

int	cd(int ac, char **av, char **env)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if ((ac == 1 || (ac == 2 && !ft_strcmp(av[1], "--"))) && !cd1(av, env, oldpwd))
		return (free(oldpwd), FALSE);
	else if (ac == 2 && ft_strcmp(av[1], "--") && !cd2(av, env, oldpwd))
		return (FALSE);
	else if (ac == 3 && !cd3(av, env, oldpwd))
		return (FALSE);
	else if (ac > 3)
	{
		free(oldpwd);
		if (!ft_strcmp(av[1], "-") || !ft_strcmp(av[1], "--") || *av[1] != '-')
			return (printfd(2, "cd: too many arguments\n"));
		else
			return (printfd(2, "cd: %c%c: invalid option\n", \
				av[1][0], av[1][1]));
	}
	pwd = getcwd(NULL, 0);
	update_env(env, "PWD=", pwd);
	update_env(env, "OLDPWD=", oldpwd);
	return (free(pwd), free(oldpwd), TRUE);
}

int main(int ac, char **av, char **envp)
{
	char **env;
	char	*a, *b;

	env = ft_arrdup(envp);
	a = getcwd(NULL, 0);
	printf("%s\n", a);
	cd(ac, av, env);
	b = getcwd(NULL, 0);
	printf("%s\n", b);
	ft_free("112", a, b , env);
	return (0);
}
