/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:55:06 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/15 11:08:24 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return ((n > 1000) + (n <= 1000 && n) * ((int)n + 1));
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
