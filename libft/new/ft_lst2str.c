/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:44:46 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/06 21:45:57 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_lst2str(t_list	*node)
{
	char	*str;
	int		i;
	int		len;

	len = ft_lstsize(node);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && node && node->content)
	{
		str[i++] = *(char *)node->content;
		node = node->next;
	}
	str[i] = '\0';
	return (str);
}
