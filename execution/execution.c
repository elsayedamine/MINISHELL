/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/30 23:38:53 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

int	check_builts(char **arr, t_shell *vars)
{
	if (!arr)
		return (FALSE);
	if (!ft_strcmp("pwd", *arr))
		return (pwd(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("cd", *arr))
		return (cd(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("echo", *arr))
		return (echo(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("env", *arr))
		return (env(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("exit", *arr))
		return (ft_exit(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("export", *arr))
		return (export(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("unset", *arr))
		return (unset(ft_arrlen(arr), arr, vars), TRUE);
	return (FALSE);
}

int	execution(t_shell *vars, t_list *ast)
{
	t_list	*node;
	int		status;
	// char	*cmd_path;
	node = ast;
	status = 0;
	while (node)
	{
		// if (node->type == CMD && node->next->type <= AND)
			// status = execute_cmd(vars, node);
		if (node->type == CMD && node->next && node->next->type == PIPE)
			status = pipex(vars, &node);
		// if (node->type == SUBSHELL)
			// status = execution(vars, node);
		// if (node->type == OR || node->type == AND)
			
		node = node->next;
	}
	return (status);
}
