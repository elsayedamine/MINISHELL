/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:08 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/18 18:25:30 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// your important task to create variadic function to set the variables to 0;

t_shell	g_vars;

void	fill_args(char *str)
{
	int	str_i;
	int	k;

	str_i = 0;
	k = 0;
	while (str[str_i])
	{
		if (str[str_i] && (ft_isalnum(str[str_i]) || !ft_strchr(",./*-+=&%$#@!", str[str_i])))
		{
			k = str_i;
			while (ft_isalnum(str[str_i]))
				str_i++;
			if (str_i > k)
				ft_lstadd_back(&g_vars.args, ft_lstnew(ft_strndup(str + k, str_i - k)));
		}
		else if (str[str_i])
		{
			ft_lstadd_back(&g_vars.args, ft_lstnew(ft_strndup(&str[str_i], 1)));
			str_i++;
		}
	}
	g_vars.tmp = g_vars.args;
	while (g_vars.tmp)
	{
		printf("%s\n", (char *)g_vars.tmp->content);
		g_vars.tmp = g_vars.tmp->next;
	}
}


void	parse_command(void)
{
	g_vars.args = NULL;
	fill_args(g_vars.cmd);
}

char	*read_cmd(char *cmd)
{
	cmd = readline("\033[1;32mminishell$ \033[0m");
	if (!cmd || !ft_strcmp("exit", cmd))
		return (NULL);
	if (*cmd)
		add_history(cmd);
	return (cmd);
}

void foo(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void prompt_loop(void)
{
	signal(SIGINT, foo);
	while (1)
	{
		g_vars.cmd = read_cmd(g_vars.cmd);
		if (!g_vars.cmd)
			return (rl_clear_history(), exit(EXIT_SUCCESS));
		parse_command();
		free(g_vars.cmd);
		ft_lstclear(&g_vars.args, free);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	if (ac != 1)
		return (EXIT_FAILURE);
	g_vars.envp = envp;
	prompt_loop();
	return (0);
}
