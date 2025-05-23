/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 02:12:01 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtins(t_shell *vars, t_fct *fct, char **arr)
{
	int	in;
	int	out;
	int exit;

	exit = 0;
	in = dup(STDIN);
	out = dup(STDOUT);
	if (in == -1 || out == -1)
		return (perror("dup"), FALSE);
	if (apply_redirections(vars) == FALSE)
		return (FALSE);
	exit = fct(ft_arrlen(arr), arr, vars);
	dup2(in, STDIN);
	dup2(out, STDOUT);
	if (in == -1 || out == -1)
		return (perror("dup2"), FALSE);
	close(in);
	close(out);
	return (exit);
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
	return (-1);
}
