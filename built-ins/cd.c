/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:06:14 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/09 15:58:31 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"


void	update_variable(char **variable, char *new_value, char *key)
{
	char *tmp;
	char *joined;

	free(*variable);
	tmp = ft_strjoin(key, "=");
	joined = ft_strjoin(tmp, new_value);
	free(tmp);
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
		if (ft_strncmp(env[i], key, ft_strlen(key)) == 0 && env[i][ft_strlen(key)] == '=')
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


int	cd(int ac, char **av, char **env)
{
	char	*oldpwd;
	char	*pwd;
	char	*home;
	if (ac > 2)
		return (dprintf(2, "cd: too many arguments\n"), FALSE);
	oldpwd = getcwd(NULL, 0);
	if (av[1] == NULL)
	{
    	home = getenv("HOME");
		if (!home || chdir(home) == -1)
		{
			dprintf(2, "cd: HOME not set or invalid\n");
			return (free(oldpwd), FALSE);
		}
		pwd = getcwd(NULL, 0);
	}
	else if(chdir(av[1]))
	{
		dprintf(2, "cd: No such file or directory\n");
		return (free(oldpwd), FALSE);
	}
	else
		pwd = getcwd(NULL, 0);
	update_env(env, "PWD", pwd);
	update_env(env, "OLDPWD", oldpwd);
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