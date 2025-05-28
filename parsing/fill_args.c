/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/28 20:00:15 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_type	define_type(char *content)
{
	if (!content)
		return (SUBSHELL);
	if (!ft_strcmp(content, "||"))
		return (OR);
	if (!ft_strcmp(content, "&&"))
		return (AND);
	if (!ft_strcmp(content, "|"))
		return (PIPE);
	if (!ft_strcmp(content, ">"))
		return (TRUNC);
	if (!ft_strcmp(content, "<"))
		return (READ);
	if (!ft_strcmp(content, ">>"))
		return (APPEND);
	if (!ft_strcmp(content, "<<"))
		return (HEREDOC);
	return (CMD);
}

t_list	*create_node(void *content)
{
	t_list	*new;

	new = (t_list *)alloc(sizeof(t_list), NULL, 'M');
	if (!new)
		return (NULL);
	new->content = content;
	new->type = define_type(content);
	new->arr = NULL;
	new->child = NULL;
	new->next = NULL;
	return (new);
}

int	validater(t_shell *vars)
{
	char	*token;

	if (!vars->cmd || !*vars->cmd)
		return (FALSE);
	token = alloc(0, tokenizer(vars->cmd, "'\"()|&<>"), 0);
	vars->args = NULL;
	while (token)
	{
		ft_lstadd_back(&vars->args, create_node(token));
		token = alloc(0, tokenizer(NULL, "'\"()|&<>"), 0);
	}
	if (!all_checks(vars))
		return (g_var->exit_status = 2, FALSE);
	if (process_heredocs(vars) == FALSE)
		return (FALSE);
	return (TRUE);
}

// void	print_ast(t_list *node, int depth)
// {
// 	while (node)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			printf("	");
// 		if (node->content)
// 			printf("- %s\n", (char *)node->content);
// 		else
// 			printf("- (group)\n");
// 		if (node->arr)
// 		{
// 			printf("	Array elements:\n");
// 			for (int i = 0; node->arr[i] != NULL; i++)
// 			{
// 				for (int j = 0; j < depth + 1; j++)
// 					printf("	");
// 				printf("- %s\n", node->arr[i]);
// 			}
// 		}
// 		if (node->child)
// 			print_ast(node->child, depth + 1);
// 		node = node->next;
// 	}
// }

int	fill_args(t_shell *vars)
{
	char	*token;

	if (validater(vars) == FALSE)
		return (FALSE);
	vars->args = NULL;
	token = alloc(0, tokenizer(vars->cmd, "'\"()|&"), 0);
	while (token)
	{
		ft_lstadd_back(&vars->args, create_node(token));
		token = alloc(0, tokenizer(NULL, "'\"()|&"), 0);
	}
	if (!nodejoin(vars))
		return (FALSE);
	vars->tmp = vars->args;
	vars->ast = ast_builder(&vars->tmp);
	return (TRUE);
}

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
