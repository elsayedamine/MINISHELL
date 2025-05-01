/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:07:20 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/30 23:22:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

int is_dir(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	return (S_ISDIR(sb.st_mode));
	// handle directory exit status and error
}

char	*handle_dir(char *path)
{
	if (is_dir(path))
	{
		printfd(2, M": %s: Is a directory\n", path);
		g_vars.exit = 126;
		return (NULL);
	}
	if (access(path, X_OK) == 0)
		return (ft_strdup(path));
	return (throw_error(ENOENT, path), NULL);
}

char	*get_path(char *full, t_shell *vars)
{
	char	**paths;
	char	*checker;
	char	*path;
	char    **cmd;
	int		i;

	cmd = ft_split(full, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
		return (handle_dir(cmd[0]));
	paths = ft_split(get_env("PATH", vars), ':');
	if (!paths || !*paths)
		return (throw_error(ENOENT, cmd[0]), NULL);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		checker = ft_strjoin(path, cmd[0]);
		if (!access(checker, X_OK) && !is_dir(checker))
		{
			if (!ft_strnstr(checker, "//", ft_strlen(checker)))
				return (ft_free("21", paths, path), checker);
		}
		ft_free("11", checker, path);
	}
	g_vars.exit = 0;
	return (ft_free("2", paths), throw_error(CMD_NOT_FOUND, cmd[0]), NULL);
}
