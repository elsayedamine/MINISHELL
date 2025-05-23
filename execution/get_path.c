/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:07:20 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 16:39:23 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_dir(const char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == -1)
		return (0);
	return (S_ISDIR(sb.st_mode));
}

char	*handle_dir(char *path, t_shell *vars)
{
	(void)vars;
	if (is_dir(path))
	{
		printfd(2, M": %s: Is a directory\n", path);
		g_var->exit_status = 126;
		return (NULL);
	}
	if (access(path, X_OK) == 0)
		return (ft_strdup(path));
	return (throw_error(ENOENT, path, NULL), NULL);
}

char	*get_path(char *cmd, t_shell *vars)
{
	char	**paths;
	char	*checker;
	char	*path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (handle_dir(cmd, vars));
	paths = ft_split(get_env("PATH", vars), ':');
	if (!paths || !*paths)
		return (throw_error(ENOENT, cmd, NULL), NULL);
	i = 0;
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i++], "/");
		checker = ft_strjoin(path, cmd);
		if (!access(checker, X_OK) && !is_dir(checker))
			if (!ft_strnstr(checker, "//", ft_strlen(checker)))
				return (ft_free("21", paths, path), checker);
		ft_free("11", checker, path);
	}
	g_var->exit_status = 127;
	return (throw_error(CMD_NOT_FOUND, cmd, &g_var->exit_status), \
		ft_free("2", paths), NULL);
}
