/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 02:29:14 by aelsayed         ###   ########.fr       */
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
		if (is_builtin == -1)
			return (FALSE);
		return (skip(ast, is_builtin), TRUE);
	}
	else if (flag == 1)
	{
		if (vars->exit == 0)
			skip(ast, OR);
		else
			traverse_sub(vars, ast);
		return (vars->exit);
	}
	return (1);
}

int	checks(t_shell *vars, t_list **ast,char **cmd)
{
	if (process_cmd(vars, ast, 0) == TRUE)
		return (vars->exit);
	if (!(*ast)->arr)
		*cmd = ft_strdup("");
	else
		*cmd = get_path((*ast)->arr[0], vars);
	if (!*cmd)
		return (skip(ast, AND), vars->exit);
	return (-1);
}

int	execute_cmd(t_shell *vars, t_list **ast)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	if (checks(vars, ast, &cmd) != -1)
		return (vars->exit);
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirections(vars) == FALSE)
			exit(errno);
		if (execve(cmd, (*ast)->arr, vars->envp) == -1)
			exit_execve(cmd, vars, ast);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			vars->exit = WEXITSTATUS(status);
	}
	return (ft_free("1",cmd), process_cmd(vars, ast, 1));
}

int	execution(t_shell *vars, t_list **ast)
{
	t_list	**node;

	node = ast;
	while (*node)
	{
		if ((*node) && (*node)->type == CMD && \
			(!(*node)->next || (*node)->next->type <= AND))
			vars->exit = execute_cmd(vars, node);
		else if ((*node) && ((*node)->type == CMD || (*node)->type == SUBSHELL)
			&& (*node)->next && (*node)->next->type == PIPE)
		{
			vars->exit = pipex(vars, node);
			traverse_sub(vars, node);
			continue ;
		}
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
//(ls && (echo A || (echo B && echo C))) || ((echo D && echo E) 
// && (echo F || echo G)) && (echo H || (echo I && (echo J || echo K)))
