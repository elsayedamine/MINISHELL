/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:48:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/06 21:59:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_cwd(char *path)
{
	char	*cwd;
	char	*full;
	char	*tmp;
	int		ret;
	int		len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	if (path[0] == '/')
		full = ft_strdup(path);
	else
	{
		tmp = ft_strjoin(cwd, "/");
		full = ft_strjoin(tmp, path);
		free(tmp);
	}
	len = ft_strlen(cwd);
	ret = 0;
	if (!ft_strncmp(full, cwd, len) && (full[len] == '/' || full[len] == '\0'))
		ret = 1;
	free(full);
	return (ret);
}

void	exit_execve(char *cmd, t_shell *vars, t_list **ast)
{
	ft_free("1", cmd);
	throw_error(CMD_NOT_FOUND, cmd, &vars->exit);
	skip(ast, AND);
}

// void	redirect(t_pip *pipe)
// {
// 	wait(NULL);
// 	close(pipe->pipefd[OUT]);
// 	if (dup2(pipe->pipefd[IN], STDIN) == -1)
// 		throw_error(DUP, NULL, NULL);
// 	close(pipe->pipefd[IN]);
// }

// void	execute_parent(t_shell *vars, t_list *node, t_pip *pipe)
// {
// 	char	*cmd;
// 	// dupliactes all the outs
// 	cmd = get_path(node->arr[0], vars);
// 	pipe->pid1 = fork();
// 	if (!pipe->pid1)
// 	{
// 		if (execve(cmd, ft_split(cmd, ' '), vars->envp) == -1)
// 			exit_execve(cmd, vars, NULL);
// 	}
// }

// // int	execute_pipe(t_shell *vars, char **args, t_list *node, t_pip *pipes)
// // {
// // 	char	*cmd;
// // 	int		i;
// // 	(void)node;
// // 	// dupicate all in ins
// // 	i = 0;
// // 	i = fork();
// // 	if (i == 0)
// // 	{
// // 		i = 0;
// // 		while (args[i])
// // 		{
// // 			if (pipe(pipes->pipefd) == -1)
// // 				return (throw_error(PIP, NULL, NULL), 1);
// // 			pipes->pid1 = fork();
// // 			if (pipes->pid1 == 0)
// // 			{
// // 				close(pipes->pipefd[IN]);
// // 				if (dup2(pipes->pipefd[OUT], STDOUT) == -1)
// // 					throw_error(DUP, NULL, NULL);
// // 				cmd = get_path(args[i], vars);
// // 				if (execve(cmd, ft_split(args[i], ' '), vars->envp) == -1)
// // 					exit_execve(cmd, vars);
// // 			}
// // 			else
// // 				redirect(pipes);
// // 			i++;
// // 		}
// // 		// execute_parent(vars, node, pipes);
// // 		while (wait(NULL) > 0)
// // 			;
// // 	}
// // 	else	
// // 		wait(NULL);
// // 	return (EXIT_SUCCESS);
// // }

// int execute_pipe(t_shell *vars, char **args, t_list *node, t_pip *pipes)
// {
// 	(void)node;
// 	(void)pipes;
// 	int		prev_fd = -1;
// 	int		pipefd[2];
// 	char	*cmd;
// 	int		i = 0;

// 	while (args[i])
// 	{
// 		if (args[i + 1])
// 			pipe(pipefd);
// 		pipes->pid1 = fork();
// 		if (pipes->pid1 == 0)
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, STDIN_FILENO);
// 				close(prev_fd);
// 			}
// 			if (args[i + 1])
// 			{
// 				close(pipefd[IN]);
// 				dup2(pipefd[OUT], STDOUT_FILENO);
// 				close(pipefd[OUT]);
// 			}
// 			cmd = get_path(args[i], vars);
// 			if (execve(cmd, ft_split(args[i], ' '), vars->envp) == -1)
// 				exit_execve(cmd, vars, NULL);
// 		}
// 		else
// 		{
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			if (args[i + 1])
// 			{
// 				close(pipefd[1]);
// 				prev_fd = pipefd[0];
// 			}
// 		}
// 		i++;
// 	}
	
// 	return (EXIT_SUCCESS);
// }


// int	pipex(t_shell *vars, t_list **node)
// {
// 	t_list	*pipeline;
// 	t_pip	pipe;

// 	pipeline = NULL;
// 	while ((*node))
// 	{
// 		if ((*node)->type == CMD && (*node)->next && (*node)->next->type == PIPE)
// 		{
// 			ft_lstadd_back(&pipeline, create_node((*node)->content));
// 			(*node) = (*node)->next->next;
// 			continue ;
// 		}
// 		if ((*node)->type == CMD)
// 			ft_lstadd_back(&pipeline, create_node((*node)->content));
// 		break ;
// 	}
// 	return (execute_pipe(vars, ft_list2arr(pipeline), *node, &pipe));
// }

int execute_pipeline(t_shell *vars, t_list *pipeline);

int pipexX(t_shell *vars, t_list **node)
{
	t_list *pipeline = NULL;
	// t_list *start = *node;
	// t_pip pipe_info;

	while (*node && ((*node)->type == CMD || (*node)->type == SUBSHELL))
	{
		ft_lstadd_back(&pipeline, *node);
		if ((*node)->next && (*node)->next->type == PIPE)
			*node = (*node)->next->next;
		else
			break;
	}
	return (execute_pipeline(vars, pipeline));
}

int execute_pipeline(t_shell *vars, t_list *pipeline)
{
	int fd[2];
	int in = 0;
	pid_t pid;
	t_list *cur = pipeline;
	int last_status = 0;

	while (cur)
	{
		if (cur->next && cur->next->type == PIPE)
			pipe(fd);

		pid = fork();
		if (pid == 0)
		{
			if (in != 0)
			{
				dup2(in, 0);
				close(in);
			}
			if (cur->next && cur->next->type == PIPE)
			{
				close(fd[0]);
				dup2(fd[1], 1);
				close(fd[1]);
			}

			if (cur->type == CMD)
				exit(execute_cmd(vars, &cur));
			else if (cur->type == SUBSHELL)
				exit(execution(vars, &cur->child));
			exit(1);
		}

		if (in != 0)
			close(in);
		if (cur->next && cur->next->type == PIPE)
		{
			close(fd[1]);
			in = fd[0];
		}

		cur = cur->next && cur->next->type == PIPE ? cur->next->next : NULL;
	}

	while (wait(&last_status) > 0);
	vars->exit = WIFEXITED(last_status) ? WEXITSTATUS(last_status) : 1;
	return (vars->exit);
}



