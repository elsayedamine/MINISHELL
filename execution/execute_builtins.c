/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/30 15:38:05 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtins(t_shell *vars, t_fct *fct, char **arr)
{
	int	in;
	int	out;
	int	exit;

	exit = 0;
	in = dup(STDIN);
	out = dup(STDOUT);
	if (in == -1 || out == -1)
		return (perror("dup"), FALSE);
	if (apply_redirections(vars) == -1)
		return (INVALID_BUILT);
	exit = fct(ft_arrlen(arr), arr, vars);
	if (dup2(in, STDIN) == -1 || dup2(out, STDOUT) == -1)
		return (perror("dup2"), FALSE);
	if (in != -1)
		close(in);
	if (out != -1)
		close(out);
	if (exit != EXIT_SUCCESS)
		return (INVALID_BUILT);
	return (VALID_BUILT);
}

int	check_builts(char **arr, t_shell *vars, int i)
{
	static char		*strs[] = {
		"export",
		"exit",
		"unset",
		"pwd",
		"echo",
		"env",
		"cd",
		NULL
	};
	static t_fct	*fcts[] = {
		export,
		ft_exit,
		unset,
		pwd,
		echo,
		env,
		cd,
	};

	while (arr && *arr && ft_strcmp(strs[i], *arr))
		i++;
	if (i != 7 && arr)
		return (execute_builtins(vars, fcts[i], arr));
	return (NOT_BUILT);
}
