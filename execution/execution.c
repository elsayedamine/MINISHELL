/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/24 18:50:15 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	process_cmd(t_shell *vars, t_list **ast, int flag)
{
	int	is_builtin;

	if (flag == 0)
	{
		(*ast)->raw = ft_strdup((*ast)->content);
		// free previous redirections
		extract_redirections(vars, (char **)&((*ast)->content));
		expand(vars, (char **)&((*ast)->content), &((*ast)->arr));
		is_builtin = check_builts((*ast)->arr, vars, 0);
		if (is_builtin == -1)
			return (FALSE);
		return (skip(ast, is_builtin), TRUE);
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

int	open_files(t_shell *vars)
{
	t_redir	*r;
	t_list	*redir;
	int		fd;
	char	*exp;

	redir = vars->redir;
	while (redir)
	{
		r = (t_redir *)redir->content;
		exp = ft_strdup(r->target);
		if (expand_target(vars, &exp) == FALSE)
			return (FALSE);
		fd = open(r->target, r->flag, 0644);
		if (fd == -1)
			return (perror(r->target), g_var->exit_status = errno, FALSE);
		close(fd);
		redir = redir->next;
	}
	return (TRUE);
}

int	checks(t_shell *vars, t_list **ast, char **cmd)
{
	if (process_cmd(vars, ast, 0) == TRUE)
		return (g_var->exit_status);
	if (!*(char *)(*ast)->content)
	{
		if (open_files(vars) == FALSE)
			return (skip(ast, AND), g_var->exit_status);
		g_var->exit_status = 0;
		return (skip(ast, OR), g_var->exit_status);
	}
	else
		*cmd = get_path((*ast)->arr[0], vars);
	if (!*cmd)
	{
		if (open_files(vars) == FALSE)
			return (skip(ast, AND), g_var->exit_status);
		throw_error(vars->err.errn, vars->err.str, NULL);
		return (skip(ast, AND), g_var->exit_status);
	}
	return (-1);
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
	{
		signal(SIGINT, SIG_DFL);
		if (apply_redirections(vars) == -1)
			exit(vars->exit);
		execve(cmd, (*ast)->arr, vars->envp);
		exit(exit_execve(cmd, vars, ast));
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_var->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			g_var->exit_status = 128 + WTERMSIG(status);
			write(1, "\n", 1);
		}
	}
	return (ft_free("1", cmd), process_cmd(vars, ast, 1));
}

int	execution(t_shell *vars, t_list **ast)
{
	t_list	**node;

	node = ast;
	while (*node)
	{
		if ((*node) && (*node)->type == CMD && \
			(!(*node)->next || (*node)->next->type <= AND))
			g_var->exit_status = execute_cmd(vars, node);
		else if ((*node) && ((*node)->type == CMD || (*node)->type == SUBSHELL)
			&& (*node)->next && (*node)->next->type == PIPE)
		{
			g_var->exit_status = pipex(vars, node);
			traverse_sub(vars, node);
			continue ;
		}
		else if ((*node) && (*node)->type == SUBSHELL)
		{
			g_var->exit_status = execution(vars, &(*node)->child);
			traverse_sub(vars, node);
			continue ;
		}
		else
			(*node) = (*node)->next;
	}
	return (g_var->exit_status);
}

// ls || (ls | ls | ls && ls) || ls && ls
// p (char *)node->content
// ls && (ls -l && ls -a || asasd||ASDSA||ASD && touch a) && touch ls
//(ls && (echo A || (echo B && echo C))) || ((echo D && echo E) 
// && (echo F || echo G)) && (echo H || (echo I && (echo J || echo K)))
