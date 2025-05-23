/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 02:08:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(int ac, char **av, t_shell *vars)
{
	char	*cwd;

	(void)vars;
	(void)ac;
	if (!av)
		return (EXIT_FAILURE);
	if (vars->pwd)
		return (printf("%s\n", vars->pwd), EXIT_SUCCESS);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror("pwd: error retrieving current directory: getcwd: cannot \
access parent directories"), EXIT_FAILURE);
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
