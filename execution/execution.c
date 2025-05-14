/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:12:24 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/14 14:10:58 by ahakki           ###   ########.fr       */
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

int	process_cmd(t_shell *vars, t_list **ast, int flag)
{
	if (flag == 0)
	{
		expand(vars, (char **)&((*ast)->content), &((*ast)->arr));
		if (check_builts((*ast)->arr, vars, 0) == TRUE)
			return (skip(ast, OR), EXIT_SUCCESS);
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

int	execute_cmd(t_shell *vars, t_list **ast)
{
	char	*cmd;
	pid_t	pid;
	int		status;

	if (process_cmd(vars, ast, 0) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
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
	return (process_cmd(vars, ast, 1));
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
//(ls && (echo A || (echo B && echo C))) || ((echo D && echo 	E) && (echo F || echo G)) && (echo H || (echo I && (echo J || echo K)))
