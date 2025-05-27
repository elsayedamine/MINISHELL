/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:15:45 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/27 23:18:14 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_built(char **arr, t_shell *vars)
{
	if (!arr)
		return (NOT_BUILT);
	if (!ft_strcmp("pwd", *arr))
		return (pwd(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("cd", *arr))
		return (cd(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("echo", *arr))
		return (echo(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("env", *arr))
		return (env(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("exit", *arr))
		return (ft_exit(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("export", *arr))
		return (export(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("unset", *arr))
		return (unset(ft_arrlen(arr), arr, vars));
	return (NOT_BUILT);
}

t_pipe	create_pipeline(t_list **ast)
{
	int		len;
	t_pipe	pipe_info;

	pipe_info.pipeline = NULL;
	len = 0;	
	while (*ast)
	{
		len++;
		if ((*ast)->type == CMD)
			ft_lstadd_back(&pipe_info.pipeline, create_node((*ast)->content));
		if ((*ast)->type == SUBSHELL)
			ft_lstadd_back(&pipe_info.pipeline, alloc(0, ft_lstnew((*ast)->child), 0));
		if ((*ast)->next && (*ast)->next->type == PIPE)
			*ast = (*ast)->next->next;
		else
			break ;
	}
	pipe_info.size = len;
	pipe_info.pos = 0;
	pipe_info.last_pid = -1;
	pipe_info.stream_line = streams_init(len);
	pipe_info.exit_status = 0;
	return (pipe_info);
}


int	wait_child_processes(t_pipe *pipe)
{
	int		status;
	int		last_status;
	pid_t	wait_pid;

	last_status = 0;
	while (1)
	{
		wait_pid = wait(&status);
		if (wait_pid == -1)
			break ;
		if (wait_pid == pipe->last_pid)
			last_status = status;
	}
	if (errno == EINTR)
		return (130);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
	{
		g_var->exit_status = 128 + WTERMSIG(last_status);
		write(1, "\n", 1);
	}
	return (1);
}
