/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/11 17:42:00 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(int ac, char **av, t_shell *vars)
{
	char	*cwd;

	(void)vars;
	if (!av)
		return (FALSE);
	if (ac != 1)
		return (printfd(2, "pwd: too many arguments\n"), TRUE);
	if (vars->pwd)
		return (printf("%s\n", vars->pwd), TRUE);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror("pwd: error retrieving current directory: getcwd: cannot \
access parent directories: No such file or directory"), FALSE);
	printf("%s\n", cwd);
	free(cwd);
	return (TRUE);
}
