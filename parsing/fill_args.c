/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/27 01:09:33 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

void	throw_error(int error)
{
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	if (error == CMD_NOT_FOUND)
		printfd(2, "Command not found : %s\n", g_vars.cmd_not_found);
	g_vars.exit = 127;
}

void	print_ast(t_list *node, int depth)
{
	while (node)
	{
		for (int i = 0; i < depth; i++)
			printf("	");
		if (node->content)
			printf("- %s\n", (char *)node->content);
		else
			printf("- (group)\n");
		if (node->arr)
		{
			printf("	Array elements:\n");
			for (int i = 0; node->arr[i] != NULL; i++)
			{
				for (int j = 0; j < depth + 1; j++)
					printf("	");
				printf("- %s\n", node->arr[i]);
			}
		}
		if (node->child)
			print_ast(node->child, depth + 1);
		node = node->next;
	}
}

t_list	*create_node(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->arr = removequotes_arr(_ft_split((char *)content, ' '));
	new->type = 0;
	new->child = NULL;
	new->next = NULL;
	return (new);
}

int	fill_args(t_shell *vars)
{
	char	*token;

	if (!vars->cmd || !*(vars->cmd) || ft_iswhitespace(vars->cmd))
		return (FALSE);
	token = ft_strtok(vars->cmd, "'\"()|&<>");
	vars->args = NULL;
	while (token)
	{
		ft_lstadd_back(&vars->args, create_node(token));
		token = ft_strtok(NULL, "'\"()|&<>");
	}
	if (!ft_check(vars))
		return (FALSE);
	vars->tmp = vars->args;
	vars->ast = ast_builder(&vars->args);
	print_ast(vars->ast, 0);
	return (TRUE);
}


// LET THE FUN BEGIN...!!
// 
t_list	*ast_builder(t_list **cursor)
{
	t_list	*node;
	t_list	*sub;
	char	*c;

	node = NULL;
	while (*cursor)
	{
		c = (char *)(*cursor)->content;
		if (!ft_strcmp(c, "("))
		{
			(*cursor) = (*cursor)->next;
			sub = create_node(NULL);
			sub->child = ast_builder(cursor);
			ft_lstadd_back(&node, sub);
		}
		else if (!ft_strcmp(c, ")"))
		{
			(*cursor) = (*cursor)->next;
			return (node);
		}
		else
		{
			ft_lstadd_back(&node, create_node(c));
			(*cursor) = (*cursor)->next;
		}
	}
	return (node);
}
