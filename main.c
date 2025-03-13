/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:08 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/13 02:44:01 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_vars;

char	*read_cmd(char *cmd)
{
	cmd = readline("\033[1;31mminishell$ \033[0m");
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

void	free_args(void)
{
	free(g_vars.cmd);
	g_vars.tmp = g_vars.args;
	while (g_vars.tmp)
	{
		if (g_vars.tmp->arr)
			ft_free("2", g_vars.tmp->arr);
		g_vars.tmp = g_vars.tmp->next;
	}
	ft_lstclear(&g_vars.args, free);
}

void	prompt_loop(void)
{
	while (1)
	{
		ft_init(6, &g_vars.check.dquot, &g_vars.check.squot, \
			&g_vars.check.par, &g_vars.check.special, &g_vars.check.fpar, \
				&g_vars.check.lpar);
		g_vars.cmd = read_cmd(g_vars.cmd);
		if (!g_vars.cmd)
			return (rl_clear_history(), exit(EXIT_SUCCESS));
		if (fill_args())
			execution();
		free_args();
	}
}

int	main(int ac, char **av, char **envp)
{
	printf("pid = %d\n", getpid());
	(void)av;
	if (ac != 1 || !envp)
		return (EXIT_FAILURE);
	g_vars.envp = envp;
	signal(SIGINT, foo);
	prompt_loop();
	return (0);
}
