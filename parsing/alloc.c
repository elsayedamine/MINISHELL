/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:49:07 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/29 22:20:39 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit2(t_list **head)
{
	int	status;

	status = g_var->exit_status;
	ft_lstclear(head, free);
	exit(status);
}

void	*alloc(size_t size, void *content, char c)
{
	static t_list	*head;
	t_list			*new_node;

	if (content)
	{
		new_node = ft_lstnew(content);
		if (!new_node)
			return (NULL);
		new_node->type = c;
		ft_lstadd_back(&head, new_node);
		return (content);
	}
	else if (c == 'M')
	{
		new_node = ft_lstnew(malloc(size));
		if (!new_node)
			return (NULL);
		new_node->type = c;
		ft_lstadd_back(&head, new_node);
		return (new_node->content);
	}
	else if (c == 'F')
		ft_exit2(&head);
	return (NULL);
}

void	*ft_list2(size_t size)
{
	return (alloc(size, NULL, 'M'));
}

void	clear(int sig)
{
	if (sig == 2)
		g_var->exit_status = 130;
	alloc(0, NULL, 'F');
}
