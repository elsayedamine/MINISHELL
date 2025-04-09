/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:03:58 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/09 16:53:52 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_option(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	echo(int ac, char **av)
{
	int i;
	int check;

	check = 0;
	i = 1;
	if (ac == 1)
		return (printf("\n"), TRUE);
	while (av[i])
	{
		if (is_option(av[i]) == 0)
			break ;
		i++;
	}
	if (i > 1)
		check = 1;
	while (av[i])
		printf("%s", av[i++]);
	if (!check)
		printf("\n");
	return (TRUE);
}

int main(int ac, char **av)
{
	echo(ac, av);
	return (0);
}