/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 02:20:13 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 03:32:20 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ast_builder(t_list **cursor)
{
	t_ast	ast;

	ast.node = NULL;
	while (*cursor)
	{
		ast.content = (char *)(*cursor)->content;
		if (!ft_strcmp(ast.content, "("))
		{
			(*cursor) = (*cursor)->next;
			ast.sub = create_node(NULL);
			ast.sub->child = ast_builder(cursor);
			ft_lstadd_back(&ast.node, ast.sub);
		}
		else if (!ft_strcmp(ast.content, ")"))
			return ((*cursor) = (*cursor)->next, ast.node);
		else
		{
			ft_lstadd_back(&ast.node, \
				create_node(alloc(0, ft_strdup(ast.content), 0)));
			(*cursor) = (*cursor)->next;
		}
	}
	return (ast.node);
}
