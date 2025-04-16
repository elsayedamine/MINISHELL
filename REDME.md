
# SEGV
    ila mssahna l env

what i did 

```char	*get_path(char **envp, char *cmd)
{
	char	**paths;

	char *(checker), *(path);
	int (i);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	if (!envp || !(*envp))
		return (throw_error(CMD_NOT_FOUND), NULL);
	paths = ft_split(envp[path_index(envp, "PATH=")] + 5, ':');
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
	g_vars.exit = 0;
	return (throw_error(CMD_NOT_FOUND), NULL);
}```

