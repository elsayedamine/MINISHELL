/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 02:27:36 by aelsayed         ###   ########.fr       */
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

int	fill_args(t_shell *vars)
{
	char	*token;

	if (validater(vars) == FALSE)
		return (FALSE);
	vars->args = NULL;
	ft_lstadd_front(&vars->args, create_node(alloc(0, ft_strdup("&&"), 0)));
	ft_lstadd_front(&vars->args, create_node(alloc(0, ft_strdup("true"), 0)));
	token = alloc(0, tokenizer(vars->cmd, "'\"()|&"), 0);
	while (token)
	{
		ft_lstadd_back(&vars->args, create_node(token));
		token = alloc(0, tokenizer(NULL, "'\"()|&"), 0);
	}
	if (ft_nodejoin(vars) == FALSE)
		return (FALSE);
	pop_spaces(vars);
	vars->tmp = vars->args;
	vars->ast = ast_builder(&vars->tmp);
	return (TRUE);
}
