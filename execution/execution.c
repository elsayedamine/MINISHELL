/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/14 01:23:57 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

int	path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!strncmp("PATH=", envp[i], 5))
			return (i);
		i++;
	}
	return (0);
}

char	*get_path(char **envp, char *cmd)
{
	char	**paths;

	char *(checker), *(path);
	int (i);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = ft_split(envp[path_index(envp)] + 5, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		checker = ft_strjoin(path, cmd);
		if (access(checker, X_OK) == 0)
			if (!ft_strnstr(checker, "//", ft_strlen(checker)))
				return (ft_free("21", paths, path), checker);
		ft_free("11", checker, path);
	}
	ft_free("2", paths);
	g_vars.cmd_not_found = cmd;
	return (throw_error(CMD_NOT_FOUND), NULL);
}

void	execution(void)
{
	char *(cmd_path);
	g_vars.tmp = g_vars.args;
	while (g_vars.tmp)
	{
		cmd_path = get_path(g_vars.envp, g_vars.tmp->arr[0]);
		if (!cmd_path)
		{
			g_vars.tmp = g_vars.tmp->next;
			continue ;
		}
		pid_t (pid) = fork();
		if (pid == 0)
		{
			if (execve(cmd_path, g_vars.tmp->arr, g_vars.envp) == -1)
				ft_free("1", cmd_path);
		}
		else
			wait(NULL);
		free(cmd_path);
		g_vars.tmp = g_vars.tmp->next;
	}
}