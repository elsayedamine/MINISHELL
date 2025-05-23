/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:48:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 16:39:32 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_execve(char *cmd, t_shell *vars, t_list **ast)
{
	(void)vars;
	throw_error(CMD_NOT_FOUND, cmd, &g_var->exit_status);
	skip(ast, AND);
}
int	execute_single_cmd(t_shell *vars, t_list *cmd_node)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	expand(vars, (char **)&(cmd_node->content), &(cmd_node->arr));
	if (check_builts(cmd_node->arr, vars, 0) == TRUE)
		return (EXIT_SUCCESS);
	cmd = get_path(cmd_node->content, vars);
	if (!cmd)
		return (g_var->exit_status);
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, cmd_node->arr, vars->envp) == -1)
			exit_execve(cmd, vars, &cmd_node);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_var->exit_status = WEXITSTATUS(status);
	}
	free(cmd);
	return (g_var->exit_status);
}


int pipex(t_shell *vars, t_list **node)
{
	int		fd[2];
	int		in_fd = STDIN_FILENO;
	pid_t	pid;
	t_list	*current = *node;

	while (current && (current->type == CMD || current->type == SUBSHELL))
	{
		t_list *next = (current->next && current->next->type == PIPE) ? current->next->next : NULL;
		if (next && pipe(fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == 0)
		{
			if (in_fd != STDIN_FILENO)
			{
				dup2(in_fd, STDIN_FILENO);
				close(in_fd);
			}
			if (next)
			{
				
				close(fd[0]);
				dup2(fd[1], STDOUT_FILENO);
				close(fd[1]);
			}
			if (current->type == CMD)
				exit(execute_cmd(vars, &current));
			else if (current->type == SUBSHELL)
				exit(execution(vars, &current->child));
			exit(EXIT_FAILURE);
		}
		else
		{
			if (in_fd != STDIN_FILENO)
				close(in_fd);
			if (next)
			{
				close(fd[1]);
				in_fd = fd[0];
			}
			waitpid(pid, &g_var->exit_status, 0);
			if (WIFEXITED(g_var->exit_status))
				g_var->exit_status = WEXITSTATUS(g_var->exit_status);
		}
		current = next;
	}
	*node = current; // Let parent continue traversal
	return (g_var->exit_status);
}
