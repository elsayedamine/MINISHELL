/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:48:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/01 00:29:40 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_execve(char *cmd)
{
	ft_free("1", cmd);
	throw_error(CMD_NOT_FOUND, cmd);
}

void	redirect(t_pip *pipe)
{
	wait(NULL);
	close(pipe->pipefd[OUT]);
	if (dup2(pipe->pipefd[IN], STDIN) == -1)
		throw_error(DUP, NULL);
	close(pipe->pipefd[IN]);
}

void	execute_parent(t_shell *vars, t_list *node, t_pip *pipe)
{
	char	*cmd;
	// dupliactes all the outs
	cmd = get_path(node->arr[0], vars);
	pipe->pid1 = fork();
	if (!pipe->pid1)
	{
		if (execve(cmd, ft_split(cmd, ' '), vars->envp) == -1)
			exit_execve(cmd);
	}
}

int	execute_pipe(t_shell *vars, char **args, t_list *node, t_pip *pipes)
{
	char	*cmd;
	int		i;
	(void)node;
	// dupicate all in ins
	i = 0;
	i = fork();
	if (i == 0)
	{
		i = 0;
		while (args[i])
		{
			if (pipe(pipes->pipefd) == -1)
				return (throw_error(PIP, NULL), 1);
			pipes->pid1 = fork();
			if (pipes->pid1 == 0)
			{
				close(pipes->pipefd[IN]);
				if (dup2(pipes->pipefd[OUT], STDOUT) == -1)
					throw_error(DUP, NULL);
				cmd = get_path(args[i], vars);
				if (execve(cmd, ft_split(args[i], ' '), vars->envp) == -1)
					exit_execve(cmd);
			}
			else
				redirect(pipes);
			i++;
		}
		// execute_parent(vars, node, pipes);
		while (wait(NULL) > 0)
			;
	}
	else	
		wait(NULL);
	return (EXIT_SUCCESS);
}

int	pipex(t_shell *vars, t_list **node)
{
	t_list	*pipeline;
	t_pip	pipe;

	pipeline = NULL;
	while ((*node))
	{
		if ((*node)->type == CMD && (*node)->next && (*node)->next->type == PIPE)
		{
			ft_lstadd_back(&pipeline, create_node((*node)->content));
			(*node) = (*node)->next->next;
			continue ;
		}
		if ((*node)->type == CMD)
			ft_lstadd_back(&pipeline, create_node((*node)->content));
		break ;
	}
	return (execute_pipe(vars, ft_list2arr(pipeline), *node, &pipe));
}
