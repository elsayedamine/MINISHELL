/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:48:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/02 11:09:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_execve(char *cmd, t_shell *vars, t_list **ast)
{
	ft_free("1", cmd);
	throw_error(CMD_NOT_FOUND, cmd, &vars->exit);
	skip(ast, AND);
}
int	check_builts(char **arr, t_shell *vars);
int	execute_single_cmd(t_shell *vars, t_list *cmd_node)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	if (check_builts(cmd_node->arr, vars) == TRUE)
		return (EXIT_SUCCESS);
	cmd = get_path(cmd_node->content, vars);
	if (!cmd)
		return (vars->exit);
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
			vars->exit = WEXITSTATUS(status);
	}
	free(cmd);
	return (vars->exit);
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
				exit(execute_single_cmd(vars, current));
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
			waitpid(pid, &vars->exit, 0);
			if (WIFEXITED(vars->exit))
				vars->exit = WEXITSTATUS(vars->exit);
		}
		current = next;
	}
	*node = current; // Let parent continue traversal
	return vars->exit;
}
