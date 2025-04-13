/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:06:14 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/13 16:44:18 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"


void	update_variable(char **variable, char *new_value, char *key)
{
	char *joined;

	free(*variable);
	joined = ft_strjoin(key, new_value);
	*variable = joined;
}


void	update_env(char **env, char *key, char* new_value)
{
	int i;

	i = 0;
	if (!key || !new_value)
		return ;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, ft_strlen(key)))
			return (update_variable(&env[i], new_value, key));
		i++;
	}
}

char **dup_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	cd2(char **av, char **env, char *oldpwd)
{
	if (av[1][0] == '-' && ft_strcmp(av[1], "--"))
		printfd(2, "cd: %s: invalid option\n", av[1]);
	else if(chdir(av[1]))
	{
		printfd(2, "cd: No such file or directory: %s\n", av[1]);
		return (free(oldpwd), FALSE);
	}
	return (TRUE);
}

int	cd3(char **av, char **env, char *oldpwd)
{
	if (ft_strcmp(av[1], "--"))
	{
		printfd(2, "cd: string not in pwd: %s\n", av[1]);
		return (free(oldpwd), FALSE);
	}
	if (chdir(av[2]))
	{
		printfd(2, "cd: No such file or directory: %s\n", av[2]);
		return (free(oldpwd), FALSE);
	}
	return (TRUE);
}

int	cd(int ac, char **av, char **env)
{
	char	*oldpwd;
	char	*pwd;
	char	*home;

	if (ac > 3 || (ac == 3 && ft_strcmp(av[1], "--")))
		return (printfd(2, "cd: too many arguments\n"), 0);
	oldpwd = getcwd(NULL, 0);
	if (ac == 1 ||(ac == 2 && !ft_strcmp(av[1], "--")))
	{
		home = getenv("HOME");
		if (!home || chdir(home) == -1)
		{
			printfd(2, "cd: HOME not set or invalid\n");
			return (free(oldpwd), FALSE);
		}
		pwd = getcwd(NULL, 0);
	}
	else if (ac == 3 && (!cd3(av, env, oldpwd)))
		return (FALSE);
	else if (ac == 2 && (!cd2(av, env, oldpwd)))
		return (FALSE);
	pwd = getcwd(NULL, 0);
	update_env(env, "PWD=", pwd);
	update_env(env, "OLDPWD=", oldpwd);
	return (free(pwd), free(oldpwd), TRUE);
}

int main(int ac, char **av, char **envp)
{
	char **env;

	env = dup_env(envp);
	printf("%s\n", getcwd(NULL, 0));
	cd(ac, av, env);
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}