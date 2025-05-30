/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:35:54 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/30 05:22:11 by aelsayed         ###   ########.fr       */
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

void	connect_pipe(t_stream *curr_stream)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		perror("pipe");
	curr_stream->write = pipefd[OUT];
	(curr_stream + 1)->read = pipefd[IN];
}

void	shut_stream(t_stream *curr_stream)
{
	if (curr_stream->read >= 0 && curr_stream->read != STDIN)
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
	if (stream->read != -1 && stream->read != STDIN_FILENO)
	{
		dup2(stream->read, STDIN_FILENO);
		close(stream->read);
	}
	if (stream->write != -1 && stream->write != STDOUT_FILENO)
	{
		dup2(stream->write, STDOUT_FILENO);
		close(stream->write);
	}
}
