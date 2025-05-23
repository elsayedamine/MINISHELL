/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 18:22:14 by aelsayed         ###   ########.fr       */
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

	new = (t_list *)malloc(sizeof(t_list));
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
	token = tokenizer(vars->cmd, "'\"()|&<>");
	vars->args = NULL;
	while (token)
	{
		ft_lstadd_back(&vars->args, create_node(token));
		token = tokenizer(NULL, "'\"()|&<>");
	}
	if (!all_checks(vars))
		return (FALSE);
	ft_lstclear(&vars->args, free);
	return (TRUE);
}

int	fill_args(t_shell *vars)
{
	char	*token;

	if (validater(vars) == FALSE)
		return (FALSE);
	vars->args = NULL;
	token = tokenizer(vars->cmd, "'\"()|&");
	while (token)
	{
		ft_lstadd_back(&vars->args, create_node(token));
		token = tokenizer(NULL, "'\"()|&");
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
			ft_lstadd_back(&node, create_node(ft_strdup(content)));
			(*cursor) = (*cursor)->next;
		}
	}
	return (node);
}
