/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:47:01 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/12 17:06:09 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *k, t_shell *vars)
{
	t_list	*tmp;

	if (!vars || !vars->env || !k)
		return (NULL);
	tmp = vars->env;
	while (tmp)
	{
		if (ft_strnstr((char *)tmp->content, k, ft_strlen(k)) == (char *)tmp->content \
			&& ((char *)tmp->content)[ft_strlen(k)] == '=')
			return ((char *)tmp->content + ft_strlen(k) + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
