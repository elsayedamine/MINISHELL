/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:03:58 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/23 16:38:46 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_option(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (FALSE);
	if (s[0] != '-')
		return (FALSE);
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (TRUE);
	return (FALSE);
}

int	echo(int ac, char **av, t_shell *vars)
{
	int	i;
	int	check;

	ft_init(2, &check, &i);
	g_var->exit_status = 0;
	(void)vars;
	if (++i && ac == 1)
		return (printf("\n"), EXIT_SUCCESS);
	while (av[i])
	{
		if (is_option(av[i]) == FALSE)
			break ;
		i++;
	}
	if (i > 1)
		check = 1;
	while (av[i])
	{
		printf("%s", av[i++]);
		if (av[i])
			printf(" ");
	}
	if (!check)
		printf("\n");
	return (EXIT_SUCCESS);
}

// int main(int ac, char **av)
// {
// 	echo(ac, av);
// 	return (0);
// }