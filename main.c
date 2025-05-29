/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:08 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 02:47:15 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	*g_var;

char	*read_cmd(t_shell *vars, char *cmd)
{
	char	*trim;

	trim = alloc(0, readline("minishell$ "), 0);
	cmd = alloc(0, ft_strtrim(trim, WHITE), 0);
	if (trim && *trim)
		add_history(trim);
	if (!trim || !ft_strcmp("exit", cmd))
		return (write(1, "exit\n", 5), clear(0), NULL);
	vars->bash_line_counter++;
	return (cmd);
}

void	foo(int sig)
{
	(void)sig;
	if (g_var->flag == 0)
	{
		g_var->exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	prompt_loop(t_shell *vars)
{
	vars->bash_line_counter = 0;
	g_var->exit_status = 0;
	while (1)
	{
		ft_init(8, &vars->check.dquot, &vars->check.squot, \
			&vars->check.par, &vars->check.special, &vars->check.fpar, \
				&vars->check.lpar, &g_var->flag, &vars->exec);
		vars->cmd = read_cmd(vars, vars->cmd);
		vars->redir = NULL;
		if (!vars->cmd)
			return ((void)alloc(0, NULL, 'F'));
		if (!*vars->cmd)
			continue ;
		g_var->flag = 1;
		if (!fill_args(vars))
			continue ;
		else
			execution(vars, &vars->ast, &vars->ast);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell		vars;

	(void)av;
	g_var = (t_sig *)alloc(sizeof(t_sig), NULL, 'M');
	if (ac != 1 || !envp)
		return (EXIT_FAILURE);
	vars.envp = ft_arrdup(envp);
	if (!*vars.envp)
		ft_nullenv(&vars);
	vars.env = ft_arr2list(vars.envp);
	vars.pwd = (char *)alloc(0, getcwd(NULL, 0), 0);
	ft_shlvl(&vars);
	signal(SIGINT, foo);
	signal(SIGQUIT, SIG_IGN);
	prompt_loop(&vars);
	return (0);
}