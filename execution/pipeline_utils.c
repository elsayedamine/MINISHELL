/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:15:45 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 02:24:00 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built(char **arr, t_shell *vars)
{
	(void)vars;
	if (!arr)
		return (0);
	return (!ft_strcmp("pwd", *arr)
		|| !ft_strcmp("cd", *arr)
		|| !ft_strcmp("echo", *arr)
		|| !ft_strcmp("env", *arr)
		|| !ft_strcmp("exit", *arr)
		|| !ft_strcmp("export", *arr)
		|| !ft_strcmp("unset", *arr));
	return (0);
}

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

t_list	*pipe_node(t_list **line, t_list *node)
{
	t_list	*new;

	if (node->type == CMD)
	{
		new = create_node(node->content);
		new->type = CMD;
		ft_lstadd_back(line, new);
	}
	if (node->type == SUBSHELL)
	{
		new = alloc(0, ft_lstnew(node->child), 0);
		new->type = SUBSHELL;
		ft_lstadd_back(line, new);
	}
	return (new);
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
		if ((*ast)->type == CMD || (*ast)->type == SUBSHELL)
			pipe_node(&pipe_info.pipeline, *ast);
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

t_stream	*streams_init(int pipeline_len)
{
	int			i;
	t_stream	*stream;

	stream = (t_stream *)alloc(sizeof(t_stream) * (pipeline_len + 1), \
		NULL, 'M');
	if (!stream)
		return (NULL);
	i = 0;
	while (i < pipeline_len)
	{
		stream[i].read = -1;
		stream[i++].write = -1;
	}
	stream[0].read = STDIN;
	stream[pipeline_len - 1].write = STDOUT;
	return (stream);
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
