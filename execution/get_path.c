/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:07:20 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/24 16:09:07 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_err(t_shell *vars, int err, char *str)
{
	vars->err.errn = err;
	vars->err.str = str;
}

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
	return (store_err(vars, ENOENT, path), NULL);
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
		return (store_err(vars, ENOENT, cmd), NULL);
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
	return (store_err(vars, CMD_NOT_FOUND, cmd), ft_free("2", paths), NULL);
}
