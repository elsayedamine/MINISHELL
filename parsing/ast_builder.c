/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:20:13 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 02:20:25 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ast_builder(t_list **cursor)
{
	t_list	*node;
	t_list	*sub;
	char	*content;

	node = NULL;
	while (*cursor)
	{
		content = (char *)(*cursor)->content;
		if (!ft_strcmp(content, "("))
		{
			(*cursor) = (*cursor)->next;
			sub = create_node(NULL);
			sub->child = ast_builder(cursor);
			ft_lstadd_back(&node, sub);
		}
		else if (!ft_strcmp(content, ")"))
			return ((*cursor) = (*cursor)->next, node);
		else
		{
			ft_lstadd_back(&node, create_node(alloc(0, ft_strdup(content), 0)));
			(*cursor) = (*cursor)->next;
		}
	}
	return (node);
}
