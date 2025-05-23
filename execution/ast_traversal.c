/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traversal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:25:11 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 02:20:57 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip(t_list **node, int op)
{
	while (*node && (*node)->next && (*node)->type != !op)
		*node = (*node)->next;
	if ((*node)->type == SUBSHELL || \
		(*node)->type == CMD || (*node)->type == !op)
		*node = (*node)->next;
}

int	traverse_sub(t_shell *vars, t_list **node)
{
	if (vars->exit == 0 && (*node) && \
		(*node)->next && (*node)->next->type == OR)
		skip(node, OR);
	else if (vars->exit != 0 && (*node) && \
		(*node)->next && (*node)->next->type == AND)
		skip(node, AND);
	else if ((*node) && (*node)->next)
		(*node) = (*node)->next->next;
	else if (*node)
		(*node) = (*node)->next;
	return (vars->exit);
}
