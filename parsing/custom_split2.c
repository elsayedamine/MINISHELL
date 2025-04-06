/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 13:45:32 by sayed             #+#    #+#             */
/*   Updated: 2025/04/03 14:37:57 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**_split(char *str, char c)
{
	t_list	*head;
	int		i;
	int		j;
	int		q;

	ft_inti(3, &i, &j, &q);
	while (str[i] == c)
		i++;
	while (str[i])
	{
		ft_lstadd_back(&head, ft_lstnew(ft_strndup(&str[i], )));
		if ((str[i] == '"' || str[i] == '\''))
			q = str[i] * (!q);
		while (str[i] != c)
		{
			
		}
		while (str[i] == c && !q)
			i++;
	}
}