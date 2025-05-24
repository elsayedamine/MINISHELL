/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 05:26:59 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/24 16:57:35 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*get_heredoc_node(t_shell *vars)
{
	t_redir	*hd;

	hd = (t_redir *)vars->heredoc->content;
	vars->heredoc = vars->heredoc->next;
	return (hd);
}

int	expand_target(t_shell *vars, char **str)
{
	t_list	*lst;
	char	**arr;
	char	*original;

	original = ft_strdup(*str);
	lst = breakdown(vars, *str);
	free(*str);
	*str = ft_lst2str(lst);
	*str = expand_wildcard(str, &lst);
	arr = split_list(lst, ' ');
	ft_lstclear(&lst, free);
	if (!arr || (ft_arrlen(arr) != 1 && *arr))
		return (vars->exit = 1, ft_free("21", arr, *str),
			throw_error(REDIR, original, NULL), ft_free("1", original), FALSE);
	return (ft_free("1", original), TRUE);
}

int	open_file(t_redir *r, char **filename)
{
	int	dup;

	r->fd = open(*filename, r->flag, 0644);
	if (r->fd < 0)
		return (perror(*filename), free(*filename), FALSE);
	if (r->mode == READ || r->mode == HEREDOC)
		dup = dup2(r->fd, STDIN);
	else
		dup = dup2(r->fd, STDOUT);
	if (dup == -1)
		return (perror("dup2"), close(r->fd), FALSE);
	if (r->mode == HEREDOC)
		unlink(r->target);
	free(r->delim);
	close(r->fd);
	return (TRUE);
}

int	apply_redirections(t_shell *vars)
{
	t_redir	*r;
	t_list	*tmp;
	char	*expanded;

	tmp = vars->redir;
	while (tmp)
	{
		r = (t_redir *)tmp->content;
		expanded = ft_strdup(r->target);
		if (r->mode != HEREDOC && expand_target(vars, &expanded) == FALSE)
			return (-1);
		if (open_file(r, &expanded) == FALSE)
		{
			vars->exit = errno;
			// close all open fds
			return (-1);
		}
		free(expanded);
		tmp = tmp->next;
	}
	return (TRUE);
}
