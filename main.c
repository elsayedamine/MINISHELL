/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:08 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/14 14:15:48 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_vars;

char	*read_cmd(char *cmd)
{
	char	*trim;

	trim = readline("minishell$ ");
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
			return (rl_clear_history(), exit(EXIT_SUCCESS));
		if (!*vars->cmd)
		{
			free(vars->cmd);
			continue ;
		}
		if (!fill_args(vars))
			free_args(0, vars);
		else
		{
			execution(vars, &vars->ast);
			free_args(1, vars);
		}
	}
}

void	ft_nullenv(t_shell *vars)
{
	char	*cwd;
	char	*j;

	cwd = getcwd(NULL, 0);
	j = ft_strjoin("_=", cwd);
	ft_free("2", vars->envp);
	vars->envp = (char **)malloc(sizeof(char *) * 5);
	(vars->envp)[0] = ft_strdup("OLDPWD");
	(vars->envp)[1] = ft_strjoin("PWD=", cwd);
	(vars->envp)[2] = ft_strdup("SHLVL=0");
	(vars->envp)[3] = ft_strjoin(j, "/./minishell");
	(vars->envp)[4] = NULL;
	ft_free("11", j, cwd);
}

int	ft_atoishell(char *str)
{
	int		i;
	int		sign;
	long	n;

	ft_init(3, &i, &sign, &n);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (sign++ && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (n > LONG_MAX / 10 || \
			(n == LONG_MAX / 10 && str[i] - '0' > LONG_MAX % 10))
			return (1);
		n = n * 10 + (str[i++] - '0');
	}
	n *= sign;
	return (n > 1000) + (n <= 1000 && n) * ((int)n + 1);
}


void	ft_shlvl(t_shell *vars)
{
	int		shlvl;
	char	*arr[3];
	char	*sh;

	shlvl = ft_atoishell(get_env("SHLVL", vars));
	sh = ft_itoa(shlvl);
	arr[0] = ft_strdup("export");
	arr[1] = ft_strjoin("SHLVL=", sh);
	arr[2] = NULL;
	export(2, arr, vars);
	ft_free("111", arr[0], arr[1], sh);
}

int	main(int ac, char **av, char **envp)
{
	t_shell		vars;

	(void)av;
	printfd(1, "pid = %d\n", getpid());
	if (ac != 1 || !envp)
		return (EXIT_FAILURE);
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
