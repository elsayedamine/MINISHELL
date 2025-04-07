/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/07 18:11:00 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(int ac, char **av)
{
	char	*cwd;

	(void)av;
	if (ac != 1)
		printfd(2, "pwd: too many arguments\n");
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		return (perror("getcwd failed"), FALSE);
	printf("%s\n", cwd);
	free(cwd);
	return (TRUE);
}
