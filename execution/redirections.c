/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:18:51 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/18 06:02:11 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	join(t_list **tokens)
{
	char	*new_content;
	char	*tmp_content;
	t_list	*to_delete;
	t_list	*tmp;

	tmp = *tokens;
	while (tmp && tmp->next)
	{
		tmp_content = (char *)tmp->content;
		if (!is_op(tmp_content) && !is_op((char *)tmp->next->content) && \
			!is_par(tmp_content) && !is_par((char *)tmp->next->content))
		{
			new_content = ft_strjoin(tmp_content, (char *)tmp->next->content);
			free(tmp->content);
			tmp->content = new_content;
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(to_delete, free);
		}
		else
			tmp = tmp->next;
	}
	return (TRUE);
}

void	pop_space(t_list **s)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*next;
	t_list	*node;

	tmp = *s;
	new = NULL;
	while (tmp)
	{
		next = tmp->next;
		if (ft_iswhitespace(tmp->content) == FALSE)
		{
			node = ft_lstnew(ft_strdup(tmp->content));
			ft_lstadd_back(&new, node);
		}
		ft_free("1", tmp->content);
		free(tmp);
		tmp = next;
	}
	*s = new;
}

t_redir	*create_redir(t_type mode, char *target)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->mode = mode;
	redir->target = target;
	redir->fd = -1;
	if (mode == READ)
		redir->flag = O_RDONLY;
	else if (mode == TRUNC)
		redir->flag = O_CREAT | O_WRONLY | O_TRUNC;
	else if (mode == APPEND)
		redir->flag = O_CREAT | O_WRONLY | O_APPEND;
	else
		redir->flag = HEREDOC;
	return (redir);
}

t_list	*extract_redirections(t_list **s)
{
	t_list	*raw;
	t_list	*tmp;
	t_list	*redir;

	tmp = *s;
	redir = NULL;
	raw = NULL;
	while (tmp)
	{
		if (tmp->type >= READ)
		{
			ft_lstadd_back(&redir, ft_lstnew(create_redir(tmp->type, \
				ft_strdup(tmp->next->content))));
			tmp = tmp->next->next;
		}
		else
		{
			ft_lstadd_back(&raw, create_node(ft_strdup(tmp->content)));
			tmp = tmp->next;
		}
	}
	ft_lstclear(s, free);
	*s = raw;
	return (redir);
}

void	redir(t_shell *vars, char **original)
{
	char	*token;
	t_list	*s;

	if (!original || !*original || !ft_strstr(*original, ">") || !ft_strstr(*original, ">>") || \
		!ft_strstr(*original, "<") || !ft_strstr(*original, "<<"))
		return ;
	s = NULL;
	token = tokenizer(*original, "<>'\" ");
	while (token)
	{
		ft_lstadd_back(&s, create_node(token));
		token = tokenizer(NULL, "<>'\" ");
	}
	join(&s);
	pop_space(&s);
	vars->redir = extract_redirections(&s);
	free(*original);
	*original = ft_lst2str(s);
	// apply_redirections(vars);
}
