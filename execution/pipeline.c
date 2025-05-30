/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 09:42:43 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/30 06:19:30 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_input(t_shell *vars, t_list *node, char *cmd, int flag)
{
	if (flag == 0)
	{
		node->raw = alloc(0, ft_strdup(node->content), 0);
		extract_redirections(vars, (char **)&node->content);
		expand(vars, (char **)&node->content, &node->arr);
	}
	else
	{
		if (check_built(node->arr, vars) != NOT_BUILT)
			clear(0);
		execve(cmd, node->arr, vars->envp);
		g_var->exit_status = 127;
		clear(0);
	}
}

int	execute_cmd_pipe(t_shell *vars, t_pipe pipe, int i)
{
	t_list	*node;
	char	*cmd;

	cmd = "";
	node = ft_lstgetnode(pipe.pipeline, i);
	if (node->type == SUBSHELL)
		return (vars->exec = execution(vars, (t_list **)&(node->content), \
			node->child), clear(0), 1);
	process_input(vars, node, cmd, 0);
	if (!*(char *)node->content && ft_strpbrk(node->raw, "'\""))
	{
		if (open_files(vars) == FALSE)
			return (1);
		return (g_var->exit_status = 1, 1);
	}
	else if (!is_built(node->arr, vars))
		cmd = alloc(0, get_path(node->arr[0], vars), 0);
	if (!cmd && open_files(vars) == FALSE)
		return (1);
	if (!cmd && (throw_error(vars->err.errn, vars->err.str, NULL), 1))
		return (g_var->exit_status = 1, 1);
	if (apply_redirections(vars) == -1)
		return (1);
	return (process_input(vars, node, cmd, 1), -1);
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
	stream2io(&pipe->stream_line[index]);
	if (index != pipe->size - 1)
		shut_stream(&pipe->stream_line[index + 1]);
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
	g_var->exit_status = wait_child_processes(&pipe);
	skip(ast, g_var->exit_status % 2);
	return (g_var->exit_status);
}
