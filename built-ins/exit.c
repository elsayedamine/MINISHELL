/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:19:39 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/20 18:37:33 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	_atoi(char const *str, int *err)
{
	unsigned int	i;
	int				sign;
	long			n;

	i = 0;
	sign = 1;
	n = 0;
	while (ft_strchr(WHITE, str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (sign == 1 && (n > (LONG_MAX - (str[i] - '0')) / 10))
			return ((*err = FALSE), -1);
		if (sign == -1 && (n < (LONG_MIN + (str[i] - '0')) / 10))
			return ((*err = FALSE), 0);
		n = n * 10 + (str[i++] - '0');
	}
	if (str[i] && !ft_isdigit(str[i]))
		*err = FALSE;
	return (n * sign);
}

unsigned char	check_args(char *str, int *error)
{
	unsigned char	result;
	char			*trim;

	trim  = ft_strtrim(str, WHITE);
	printf("%s'\n", trim);
	result = (unsigned char)_atoi(trim, error);
	return (free(trim), result);
}

int	ft_exit(int ac, char **av, t_shell *vars)
{
	unsigned char	round;
	int				error;

	write(1, "exit\n", 5);
	error = TRUE;
	if (ac <= 1)
	{
		// clear();
		exit(vars->exit);
	}
	round = check_args(av[1], &error);
	if (error == FALSE)
	{
		printfd(2, M": exit: numeric argument required\n");
		// clear();
		exit(2);
	}
	if (ac > 2)
	{
		vars->exit = 1;
		return (printfd(2, "exit: too many arguments\n"), FALSE);
	}
	// clear();
	return (exit(round), TRUE);
}

// int main(int ac, char **av)
// {
// 	t_shell vars;

// 	vars.exit = 0;

// 	ft_exit(ac, av, &vars);
// 	exit(vars.exit);
// 	return (0);
// }
