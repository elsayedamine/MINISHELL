/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:07:20 by aelsayed          #+#    #+#             */
/*   Updated: 2025/07/03 09:06:21 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_cmd(t_shell *vars, t_list **ast, int flag)
{
	int	is_builtin;

	if (flag == 0)
	{
		extract_redirections(vars, (char **)&((*ast)->content));
		expand(vars, (char **)&((*ast)->content), &((*ast)->arr));
		is_builtin = check_builts((*ast)->arr, vars, 0);
		if (is_builtin == INVALID_BUILT || is_builtin == VALID_BUILT)
			return (skip(ast, is_builtin % 2), is_builtin);
		if (is_builtin == NOT_BUILT)
			return (is_builtin);
	}
	else if (flag == 1)
	{
		if (g_var->exit_status == 0)
			skip(ast, OR);
		else
			traverse_sub(vars, ast);
		return (g_var->exit_status);
	}
	return (1);
}

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
	else if (access(path, X_OK) == 0)
		return (ft_strdup(path));
	else if (access(path, F_OK) == 0)
	{
		g_var->exit_status = 126;
		return (store_err(vars, EACCES, path), NULL);
	}
	g_var->exit_status = 127;
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
