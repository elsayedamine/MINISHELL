/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/07 17:30:05 by aelsayed         ###   ########.fr       */
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
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror("getcwd failed"), FALSE);
	printf("%s\n", cwd);
	free(cwd);
	return (TRUE);
}
