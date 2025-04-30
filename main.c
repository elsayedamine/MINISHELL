/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:08 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/30 04:14:49 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_vars;

char	*read_cmd(char *cmd)
{
	char	*trim;

	trim = readline("\033[1;31mminishell$ \033[0m");
	cmd = ft_strtrim(trim, " \t\n\v\r\f");
	free(trim);
	if (!cmd || !ft_strcmp("exit", cmd))
		return (NULL);
	if (*cmd)
		add_history(cmd);
	return (cmd);
}

void	foo(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	free_args(int flag, t_shell *vars)
{
	free(vars->cmd);
	vars->tmp = vars->args;
	while (flag && vars->tmp)
	{
		if (vars->tmp->arr)
			ft_free("2", vars->tmp->arr);
		vars->tmp = vars->tmp->next;
	}
	ft_lstclear(&vars->args, free);
}

void	prompt_loop(t_shell *vars)
{
	while (1)
	{
		ft_init(7, &vars->check.dquot, &vars->check.squot, \
			&vars->check.par, &vars->check.special, &vars->check.fpar, \
				&vars->check.lpar, &vars->exit);
		vars->cmd = read_cmd(vars->cmd);
		if (!vars->cmd)
			return (rl_clear_history(), printf("exit\n"),exit(EXIT_SUCCESS));
		if (!*vars->cmd)
		{
			free(vars->cmd);
			continue ;
		}
		if (!fill_args(vars))
			free_args(0, vars);
		else
		{
			execution(vars);
			free_args(1, vars);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	vars;

	(void)av;
	printfd(1, "pid = %d\n", getpid());
	if (ac != 1 || !envp)
		return (EXIT_FAILURE);
	// if (write(1, 0, 0) == -1 || read(0, 0, 0) == -1)
	// 	return (write(2, "amine\n", 6));
	// we should handle 1 and 0 fd close
	vars.envp = ft_arrdup(envp);
	vars.env = ft_arr2list(vars.envp);
	signal(SIGINT, foo);
	prompt_loop(&vars);
	return (0);
}
