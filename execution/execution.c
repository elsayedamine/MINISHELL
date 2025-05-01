/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/01 18:53:03 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

int	check_builts(char **arr, t_shell *vars)
{
	if (!arr)
		return (FALSE);
	if (!ft_strcmp("pwd", *arr))
		return (pwd(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("cd", *arr))
		return (cd(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("echo", *arr))
		return (echo(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("env", *arr))
		return (env(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("exit", *arr))
		return (ft_exit(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("export", *arr))
		return (export(ft_arrlen(arr), arr, vars), TRUE);
	if (!ft_strcmp("unset", *arr))
		return (unset(ft_arrlen(arr), arr, vars), TRUE);
	return (FALSE);
}

void	skip(t_list **node, int op)
{
	while (*node && (*node)->next && (*node)->type != !op)
		*node = (*node)->next;
	if ((*node)->type == SUBSHELL || (*node)->type == CMD || (*node)->type == !op)
		*node = (*node)->next;
}

int	execute_cmd(t_shell *vars, t_list **ast)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	if (check_builts((*ast)->arr, vars) == TRUE)
		return (skip(ast, OR), EXIT_SUCCESS);
	cmd = get_path((*ast)->content, vars);
	if (!cmd)
		return (skip(ast, AND), vars->exit);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd, (*ast)->arr, vars->envp) == -1)
			exit_execve(cmd, vars, ast);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			vars->exit = WEXITSTATUS(status);
	}
	free(cmd);
	if (vars->exit == 0)
		skip(ast, OR);
	else
		traverse_sub(vars, ast);
	return (vars->exit);
}

int	traverse_sub(t_shell *vars, t_list **node)
{
	if (vars->exit == 0 && (*node)->next && (*node)->next->type == OR)
		skip(node, OR);
	else if (vars->exit != 0 && (*node)->next && (*node)->next->type == AND)
		skip(node, AND);
	else if ((*node)->next)
		(*node) = (*node)->next->next;
	else
		(*node) = (*node)->next;
	return (vars->exit);
}

int	execution(t_shell *vars, t_list **ast)
{
	t_list	**node;
	// char	*cmd_path;
	node = ast;
	while (*node)
	{
		if ((*node) && (*node)->type == CMD && (!(*node)->next || (*node)->next->type <= AND))
			vars->exit = execute_cmd(vars, node);
		else if ((*node) && (*node)->type == CMD && (*node)->next && (*node)->next->type == PIPE)
			vars->exit = pipex(vars, node);
		else if ((*node) && (*node)->type == SUBSHELL)
		{
			vars->exit = execution(vars, &(*node)->child);
			traverse_sub(vars, node);
			continue ;
		}
		else
			(*node) = (*node)->next;
	}
	return (vars->exit);
}
// ls || (ls | ls | ls && ls) || ls && ls
// p (char *)node->content
// ls && (ls -l && ls -a || asasd||ASDSA||ASD && touch a) && touch ls
// (ls && (echo A || (echo B && echo C))) || ((echo D && echo E) && (echo F || echo G)) 
 // && (echo H || (echo I && (echo J || echo K)))