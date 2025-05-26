/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:48:32 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/25 02:17:21 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_execve(char *cmd, t_shell *vars, t_list **ast)
{
	(void)vars;
	throw_error(CMD_NOT_FOUND, cmd, &g_var->exit_status);
	skip(ast, AND);
	return (errno);
}

char	**extract_pipeline(t_list **node)
{
	t_list	*pipeline;
	t_list	*tmp;

	pipeline = NULL;
	tmp = *node;
	while (tmp)
	{
		if (tmp->type == CMD && tmp->next && tmp->next->type == PIPE)
		{
			ft_lstadd_back(&pipeline, create_node(alloc(0, ft_strdup(tmp->content), 0)));
			tmp = tmp->next;
		}
		else if (tmp->type == CMD)
			ft_lstadd_back(&pipeline, create_node(alloc(0, ft_strdup(tmp->content), 0)));
		else
			break ;
		tmp = tmp->next;
	}
	return (ft_list2arr(pipeline));
}

int	pipex(t_shell *vars, t_list **node)
{
	char	**cmds;

	(void)vars;
	cmds = extract_pipeline(node);
	return (1);
}
