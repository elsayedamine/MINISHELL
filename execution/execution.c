/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/13 19:22:38 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_builts(char **arr, t_shell *vars, int i)
{
	static char		*strs[] = {
		"export",
		"exit",
		"unset",
		"pwd",
		"echo",
		"env",
		"cd",
		NULL
	};
	static t_fct	*fcts[] = {
		export,
		ft_exit,
		unset,
		pwd,
		echo,
		env,
		cd,
	};

	while (ft_strcmp(strs[i], *arr))
		i++;
	if (i != 7)
		return (fcts[i](ft_arrlen(arr), arr, vars), TRUE);
	return (FALSE);
}

void	skip(t_list **node, int op)
{
	while (*node && (*node)->next && (*node)->type != !op)
		*node = (*node)->next;
	if ((*node)->type == SUBSHELL || \
		(*node)->type == CMD || (*node)->type == !op)
		*node = (*node)->next;
}

int	execute_cmd(t_shell *vars, t_list **ast)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	expand(vars, (char **)&((*ast)->content), &((*ast)->arr));
	if (check_builts((*ast)->arr, vars, 0) == TRUE)
		return (skip(ast, OR), EXIT_SUCCESS);
	if (!(*ast)->arr)
		return (traverse_sub(vars, ast), 0);
	cmd = get_path((*ast)->arr[0], vars);
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
	if (vars->exit == 0 && (*node) && \
		(*node)->next && (*node)->next->type == OR)
		skip(node, OR);
	else if (vars->exit != 0 && (*node) && \
		(*node)->next && (*node)->next->type == AND)
		skip(node, AND);
	else if ((*node) && (*node)->next)
		(*node) = (*node)->next->next;
	else
		(*node) = (*node)->next;
	return (vars->exit);
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
//(ls && (echo A || (echo B && echo C))) || ((echo D && echo 	E)
//&& (echo F || echo G)) && (echo H || (echo I && (echo J || echo K)))
