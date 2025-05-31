/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_traversal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:25:11 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 06:06:34 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip(t_list **node, int op)
{
	if (g_var->fst_cmd == -1)
	{
		(*node) = (*node)->next->next;
		return ;
	}
	while (*node && (*node)->next && (*node)->type != !op)
		*node = (*node)->next;
	if ((*node)->type == SUBSHELL || \
		(*node)->type == CMD || (*node)->type == !op)
		*node = (*node)->next;
}

int	traverse_sub(t_shell *vars, t_list **node)
{
	(void)vars;
	if ((*node) && !(*node)->content && \
		(*node)->next && (*node)->next->type == CMD)
		(*node) = (*node)->next;
	if (g_var->exit_status == 0 && (*node) && \
		(*node)->next && (*node)->next->type == OR)
		skip(node, OR);
	else if (g_var->exit_status != 0 && (*node) && \
		(*node)->next && (*node)->next->type == AND)
		skip(node, AND);
	else if ((*node) && (*node)->next)
		(*node) = (*node)->next->next;
	else if (*node)
		(*node) = (*node)->next;
	return (g_var->exit_status);
}
