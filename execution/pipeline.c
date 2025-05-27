/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:42:43 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/27 23:28:20 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_execve(char *cmd, t_shell *vars, t_list **ast)
{
	(void)vars;
	g_var->exit_status = 127;
	throw_error(CMD_NOT_FOUND, cmd, NULL);
	skip(ast, AND);
	return (errno);
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

void	connect_pipe(t_stream *curr_stream)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		perror("pipe");
	(*curr_stream).write = pipefd[IN];
	(*(curr_stream + 1)).read = pipefd[OUT];
}

void	shut_stream(t_stream *curr_stream)
{
	if (curr_stream->read > 0)
	{
		close(curr_stream->read);
		curr_stream->read = -1;
	}
	if (curr_stream->write >= 0 && curr_stream->write != STDOUT)
	{
		close(curr_stream->write);
		curr_stream->write = -1;
	}
}

void	stream2io(t_stream *stream)
{
	if (stream->read != STDIN_FILENO)
		if (dup2(stream->read, STDIN_FILENO) == -1)
			perror(strerror(errno));
	if (stream->write != STDOUT_FILENO)
		if (dup2(stream->write, STDOUT_FILENO) == -1)
			perror(strerror(errno));
	shut_stream(stream);
}

int	execute_cmd_pipe(t_shell *vars, t_pipe pipe, int i)
{
	t_list	*node;
	pid_t	pid;
	char	*cmd;

	node = ft_lstgetnode(pipe.pipeline, i);
	if (node->type == SUBSHELL)
		return (execution(vars, &node));
	node->raw = alloc(0, ft_strdup(node->content), 0);
	extract_redirections(vars, (char **)&node->content);
	expand(vars, (char **)&node->content, &node->arr);
	stream2io(&pipe.stream_line[i]);
	// if (apply_redirections(vars) == -1)
	// 	return (-1);
	if (!*(char *)node->content && ft_strpbrk(node->raw, "'\""))
	{
		if (open_files(vars) == FALSE)
			return (-1);
		return (g_var->exit_status = 0, 0);
	}
	else
		cmd = alloc(0, get_path(node->arr[0], vars), 0);
	if (!cmd)
	{
		if (open_files(vars) == FALSE)
			return (-1);
		throw_error(vars->err.errn, vars->err.str, NULL);
		return (g_var->exit_status = 0, 0);
	}
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid > 0)
		return (pid);
	signal(SIGINT, clear);
	if (i != pipe.size -1)
		shut_stream	(&pipe.stream_line[i + 1]);
	if (apply_redirections(vars) == -1)
		return (-1);
	int builts = check_built(node->arr, vars);
	if (builts != NOT_BUILT)
		clear(0);
	execve(cmd, node->arr, vars->envp);
	g_var->exit_status = 127;
	clear(0);
	return (-1);
}

pid_t	execute_pipe(t_shell *vars, t_pipe *pipe, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	else if (pid > 0)
	{
		signal(SIGINT, SIG_IGN);
		if (index == pipe->size - 1)
			signal(SIGINT, foo);
		return (pid);
	}
	signal(SIGINT, clear);
	if (index != pipe->size - 1)
		shut_stream(&pipe->stream_line[index]);
	g_var->exit_status = execute_cmd_pipe(vars, *pipe, index);
	clear(0);
	return (-1);
}

int	pipex(t_shell *vars, t_list **ast)
{
	t_pipe	pipe;

	pipe = create_pipeline(ast);
	while (pipe.pos < pipe.size)
	{
		if (pipe.pos < pipe.size - 1)
			connect_pipe(&pipe.stream_line[pipe.pos]);
		pipe.last_pid = execute_pipe(vars, &pipe, pipe.pos);
		shut_stream(&pipe.stream_line[pipe.pos++]);
	}
	pipe.exit_status = wait_child_processes(&pipe);
	skip(ast, (pipe.exit_status != 0));
	return (pipe.exit_status);
}
