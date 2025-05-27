/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:48:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/26 17:04:46 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_execve(char *cmd, t_shell *vars, t_list **ast)
{
	(void)vars;
	throw_error(CMD_NOT_FOUND, cmd, &g_var->exit_status);
	skip(ast, AND);
	return (errno);
}

int		exit_execves(char *cmd, t_shell *vars);
t_list	*extract_pipeline(t_list **node);
void	execute_pipeline(t_shell *vars, t_list *node);
int		pipex(t_shell *vars, t_list **node);
void	redirect(int pipefd[2]);
int		parent(t_shell *vars, t_list *node);
int		process_cmmd(t_shell *vars, t_list *node);
int		open_files(t_shell *vars);
int		check_cmd(t_shell *vars, t_list *node, char **cmd);
int		execute_pipe(t_shell *vars, t_list *node);


int	exit_execves(char *cmd, t_shell *vars)
{
	(void)vars;
	throw_error(CMD_NOT_FOUND, cmd, &g_var->exit_status);
	return (errno);
}

t_list	*extract_pipeline(t_list **node)
{
	t_list	*pipeline;
	t_list	*tmp;

	pipeline = NULL;
	tmp = *node;
	while (tmp)
	{
		if (tmp->type == CMD && tmp->next && tmp->next->type == PIPE)
		{
			ft_lstadd_back(&pipeline, create_node(alloc(0, ft_strdup(tmp->content), 0)));
			tmp = tmp->next;
		}
		else if (tmp->type == CMD)
			ft_lstadd_back(&pipeline, create_node(alloc(0, ft_strdup(tmp->content), 0)));
		else
			break ;
		tmp = tmp->next;
	}
	return (pipeline);
}

int	pipex(t_shell *vars, t_list **node)
{
	t_list	*pipeline;

	(void)vars;
	pipeline = extract_pipeline(node);
	execute_pipeline(vars, pipeline);
	traverse_sub(vars, node);
	return (1);
}

// void	redirect(int pipefd[2], int *fd)
// {
// 	if (*fd != -1)
// 		close(*fd);
// 	*fd = -1;
// 	close(pipefd[OUT]);
// 	if (dup2(pipefd[IN], STDIN) == -1)
// 		perror("dup2");
// 	close(pipefd[IN]);
// 	//signals
// }

// int	parent(t_shell *vars, t_list *node)
// {
// 	char	*cmd;
// 	pid_t pid = fork();
// 	if (pid == 0)
// 	{
// 		if (check_cmd(vars, node, &cmd) != -1)
// 			return (g_var->exit_status);
// 		signal(SIGINT, SIG_IGN);
// 		if (apply_redirections(vars) == -1)
// 			clear(0);
// 		execve(cmd, node->arr, vars->envp);
// 		g_var->exit_status = exit_execves(cmd, vars);
// 		clear(0);
// 		signal(SIGINT, foo);
// 	}
// 	return (g_var->exit_status);
// }

void	execute_pipeline(t_shell *vars, t_list *node)
{
	// int		pipefd[2];
	// pid_t	pid;
	// int 	prev_fd = -1;

	// while (node && node->next && node->next->next)
	// {
	// 	if (pipe(pipefd) == -1)
	// 		return (perror("pipe"));
	// 	pid = fork();
	// 	if (pid == 0)
	// 	{
	// 		if (prev_fd != -1)
    //         {
    //             dup2(prev_fd, STDIN_FILENO);
    //             close(prev_fd);
    //         }
	// 		close(pipefd[IN]);
	// 		if (dup2(pipefd[OUT], STDOUT) == -1)
	// 			return (perror("dup2"));
	// 		close(pipefd[OUT]);
	// 		execute_pipe(vars, node);
	// 		exit(exit_execves(node->content, vars));
	// 	}
	// 	else
	// 	{
	// 		if (prev_fd != -1)
	// 			close(prev_fd);
	// 		if (node->next && node->next->type == PIPE)
	// 		{
	// 			close(pipefd[1]);
	// 			prev_fd = pipefd[0];
	// 		}
	// 		else
	// 			prev_fd = -1;
	// 		if (node->next && node->next->type == PIPE)
	// 			node = node->next->next;
	// 		else
	// 			node = NULL;
	// 	}
	// }
	execute_cmd(vars, &node);
}

int	process_cmmd(t_shell *vars, t_list *node)
{
	int	is_builtin;

	node->raw = ft_strdup(node->content);
	alloc(0, node->raw, 0);
	extract_redirections(vars, (char **)&(node->content));
	expand(vars, (char **)&(node->content), &(node->arr));
	is_builtin = check_builts(node->arr, vars, 0);
	if (is_builtin == -1)
		return (FALSE);
	return (TRUE);
}

int	check_cmd(t_shell *vars, t_list *node, char **cmd)
{
	if (process_cmmd(vars, node) == TRUE)
		return (g_var->exit_status);
	if (!*(char *)node->content)
	{
		if (open_files(vars) == FALSE)
			return (g_var->exit_status);
		g_var->exit_status = 0;
		return (g_var->exit_status);
	}
	else
		*cmd = alloc(0, get_path(node->arr[0], vars), 0);
	if (!*cmd)
	{
		if (open_files(vars) == FALSE)
			return (g_var->exit_status);
		throw_error(vars->err.errn, vars->err.str, NULL);
		return (g_var->exit_status);
	}
	return (-1);
}

int	execute_pipe(t_shell *vars, t_list *node)
{
	char	*cmd;

	if (check_cmd(vars, node, &cmd) != -1)
		return (g_var->exit_status);
	signal(SIGINT, SIG_DFL);
	if (apply_redirections(vars) == -1)
		clear(0);
	execve(cmd, node->arr, vars->envp);
	g_var->exit_status = exit_execves(cmd, vars);
	clear(0);
	return (g_var->exit_status);
}
