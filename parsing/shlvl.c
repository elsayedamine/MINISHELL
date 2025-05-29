/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:55:06 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 22:20:00 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_nullenv(t_shell *vars)
{
	char	*cwd;
	char	*j;

	cwd = (char *)alloc(0, getcwd(NULL, 0), 0);
	j = (char *)alloc(0, ft_strjoin("_=", cwd), 0);
	vars->envp = (char **)alloc(sizeof(char *) * 5, NULL, 'M');
	(vars->envp)[0] = (char *)alloc(0, ft_strdup("OLDPWD"), 0);
	(vars->envp)[1] = (char *)alloc(0, ft_strjoin("PWD=", cwd), 0);
	(vars->envp)[2] = (char *)alloc(0, ft_strdup("SHLVL=0"), 0);
	(vars->envp)[3] = (char *)alloc(0, ft_strjoin(j, "/./minishell"), 0);
	(vars->envp)[4] = NULL;
}

int	ft_atoishell(char *str)
{
	int		i;
	int		sign;
	long	n;

	ft_init(2, &i, &sign);
	n = 0;
	if (!str)
		return (1);
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
	char	*env_shlvl;

	env_shlvl = get_env("SHLVL", vars);
	if (env_shlvl == NULL || ft_atoishell(env_shlvl) == 0)
		shlvl = 1;
	else
		shlvl = ft_atoishell(env_shlvl);
	sh = ft_itoa(shlvl);
	arr[0] = ft_strdup("export");
	arr[1] = ft_strjoin("SHLVL=", sh);
	arr[2] = NULL;
	export(2, arr, vars);
	ft_free("111", arr[0], arr[1], sh);
}
