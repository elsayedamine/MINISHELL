/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 06:00:45 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_cmd(t_shell *vars, t_list **ast, int flag)
{
	int	is_builtin;

	if (flag == 0)
	{
		extract_redirections(vars, (char **)&((*ast)->content));
		expand(vars, (char **)&((*ast)->content), &((*ast)->arr));
		is_builtin = check_builts((*ast)->arr, vars, 0);
		if (is_builtin == INVALID_BUILT || is_builtin == VALID_BUILT)
			return (skip(ast, is_builtin % 2), is_builtin);
		if (is_builtin == NOT_BUILT)
			return (is_builtin);
	}
	else if (flag == 1)
	{
		if (g_var->exit_status == 0)
			skip(ast, OR);
		else
			traverse_sub(vars, ast);
		return (g_var->exit_status);
	}
	return (1);
}

int	checks(t_shell *vars, t_list **ast, char **cmd)
{
	int	is_valid;

	is_valid = process_cmd(vars, ast, 0);
	if (is_valid == VALID_BUILT || is_valid == INVALID_BUILT)
		return (g_var->exit_status);
	if (!*(char *)(*ast)->content)
	{
		if (open_files(vars) == FALSE)
			return (skip(ast, AND), g_var->exit_status);
		g_var->exit_status = 0;
		return (skip(ast, OR), g_var->exit_status);
	}
	else
		*cmd = alloc(0, get_path((*ast)->arr[0], vars), 0);
	if (!*cmd)
	{
		if (open_files(vars) == FALSE)
			return (skip(ast, AND), g_var->exit_status);
		throw_error(vars->err.errn, vars->err.str, NULL);
		return (skip(ast, AND), g_var->exit_status);
	}
	return (-1);
}

void	child_cmd(t_shell *vars, t_list **ast, char *cmd)
{
	signal(SIGINT, clear);
	if (apply_redirections(vars) == -1)
		clear(0);
	execve(cmd, (*ast)->arr, vars->envp);
	g_var->exit_status = exit_execve(cmd, vars, ast);
	clear(0);
}

int	execute_cmd(t_shell *vars, t_list **ast)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	if (checks(vars, ast, &cmd) != -1)
		return (g_var->exit_status);
	pid = fork();
	if (pid == 0)
		child_cmd(vars, ast, cmd);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, foo);
		if (WIFEXITED(status) && g_var->fst_cmd != -1)
			g_var->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_var->exit_status = 130;
			write(1, "\n", 1);
		}
	}
	return (process_cmd(vars, ast, 1), g_var->exit_status);
}

int	execution(t_shell *vars, t_list **ast, t_list *parent)
{
	t_list	**node;

	node = ast;
	redirect_sub(vars, ast, parent);
	while (*node)
	{
		if ((*node) && (*node)->type == CMD && \
			(!(*node)->next || (*node)->next->type <= AND))
			g_var->exit_status = (g_var->fst_cmd != -1) * execute_cmd(vars, node) + g_var->exit_status * (g_var->fst_cmd == -1);
		else if (is_valid_pipex(node))
			g_var->exit_status = pipex(vars, node);
		else if ((*node) && (*node)->type == SUBSHELL)
		{
			g_var->exit_status = execution(vars, &(*node)->child, *node);
			traverse_sub(vars, node);
		}
		else
			(*node) = (*node)->next;
		vars->redir = NULL;
		g_var->fst_cmd = 0;
	}
	return (return_original_std(vars), g_var->exit_status);
}
