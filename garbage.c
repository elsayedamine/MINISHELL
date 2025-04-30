/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 03:48:48 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/30 03:49:38 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_in_cwd(char *path)
{
	char	*cwd;
	char	*full;
	char	*tmp;
	int		ret;
	int		len;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	if (path[0] == '/')
		full = ft_strdup(path);
	else
	{
		tmp = ft_strjoin(cwd, "/");
		full = ft_strjoin(tmp, path);
		free(tmp);
	}
	len = ft_strlen(cwd);
	ret = 0;
	if (!ft_strncmp(full, cwd, len) && (full[len] == '/' || full[len] == '\0'))
		ret = 1;
	free(full);
	return (ret);
}
