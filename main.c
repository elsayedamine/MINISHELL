/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:08 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 03:03:45 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_var = 0;

char	*read_cmd(char *cmd)
{
	char	*trim;

	trim = readline("minishell$ ");
	cmd = ft_strtrim(trim, WHITE);
	if (trim && *trim)
		add_history(trim);
	free(trim);
	if (!trim || !ft_strcmp("exit", cmd))
		return (NULL);
	return (cmd);
}

void	foo(int sig)
{
	(void)sig;
	if (g_var == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
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
	vars->exit = 0;
	while (1)
	{
		ft_init(7, &vars->check.dquot, &vars->check.squot, \
			&vars->check.par, &vars->check.special, &vars->check.fpar, \
				&vars->check.lpar, &g_var);
		vars->cmd = read_cmd(vars->cmd);
		if (!vars->cmd)
			return (rl_clear_history(), exit(EXIT_SUCCESS));
		if (!*vars->cmd)
		{
			free(vars->cmd);
			continue ;
		}
		g_var = 1;
		if (!fill_args(vars))
			free_args(0, vars);
		else
		{
			execution(vars, &vars->ast);
			free_args(1, vars);
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		vars;

	(void)av;
	if (ac != 1 || !envp)
		return (EXIT_FAILURE);
	// printfd(1, "pid = %d\n", getpid());
	vars.envp = ft_arrdup(envp);
	if (!*vars.envp)
		ft_nullenv(&vars);
	vars.env = ft_arr2list(vars.envp);
	vars.pwd = getcwd(NULL, 0);
	ft_shlvl(&vars);
	signal(SIGINT, foo);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop(&vars);
	return (0);
}
