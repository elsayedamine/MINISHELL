/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 23:15:45 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 06:31:27 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		new->child = node;
		new->type = SUBSHELL;
		ft_lstadd_back(line, new);
	}
	return (new);
}

int	traverse_pipie(t_list **ast)
{
	if ((*ast)->next && (*ast)->next->type == CMD)
	{
		if ((*ast)->next->next && (*ast)->next->next->type == PIPE)
			(*ast) = (*ast)->next->next->next;
		else
		{
			(*ast) = (*ast)->next;
			return (FALSE);
		}
	}
	else if ((*ast)->next && (*ast)->next->type == PIPE)
		(*ast) = (*ast)->next->next;
	else
		return (FALSE);
	return (TRUE);
}

t_pipe	create_pipeline(t_list **ast)
{
	t_pipe	pipe_info;

	pipe_info.pipeline = NULL;
	ft_init(2, &pipe_info.size, &pipe_info.pos);
	while ((*ast))
	{
		if (((*ast)->type == CMD || (*ast)->type == SUBSHELL))
		{
			pipe_node(&pipe_info.pipeline, (*ast));
			pipe_info.size++;
		}
		if ((*ast)->type == SUBSHELL)
		{
			if (traverse_pipie(ast) == FALSE)
				break ;
		}
		else if ((*ast)->next && (*ast)->next->type == PIPE)
			(*ast) = (*ast)->next->next;
		else
			break ;
	}
	pipe_info.last_pid = -1;
	pipe_info.stream_line = streams_init(pipe_info.size);
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
	int		sigint_flag;
	pid_t	wait_pid;

	ft_init(2, &last_status, &sigint_flag);
	while (1)
	{
		wait_pid = wait(&status);
		if (wait_pid == -1)
			break ;
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				sigint_flag = 1;
		}
		if (wait_pid == pipe->last_pid)
			last_status = status;
	}
	if (errno == EINTR || sigint_flag)
		return (write(1, "\n", 1), g_var->exit_status = 130, 130);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	return (1);
}
