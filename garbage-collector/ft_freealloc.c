/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freealloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:51:24 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/17 22:46:03 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lst_add_back(t_list **head, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_list	*ft_lst_new(size_t size)
{
	t_list	*new_node;
	void	*content;

	content = malloc(size);
	if (!content)
		return (NULL);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (free(content), NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	free_all_memory(t_list **head)
{
	t_list	*temp;
	t_list	*help;

	temp = *head;
	while (temp)
	{
		help = temp;
		temp = temp->next;
		if (help->content)
			free(help->content);
		free(help);
	}
}
