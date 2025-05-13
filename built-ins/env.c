/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:38:48 by sayed             #+#    #+#             */
/*   Updated: 2025/05/13 19:10:37 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(int ac, char **av, t_shell *vars)
{
	t_list	*tmp;
	char	*str;

	(void)av;
	tmp = vars->env;
	if (ac != 1)
		return (printfd(2, "env: No options or "), \
			printfd(2, "arguments are allowed!\n"), TRUE);
	while (tmp)
	{
		str = (char *)tmp->content;
		if (ft_strchr(str, '='))
			printf("%s\n", str);
		tmp = tmp->next;
	}
	return (TRUE);
}
