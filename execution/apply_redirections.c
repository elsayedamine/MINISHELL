/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 05:26:59 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/19 04:11:16 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_target(t_shell *vars, char **str)
{
	t_list	*lst;
	char	**arr;

	lst = breakdown(vars, str);
	free(*str);
	*str = ft_lst2str(lst);
	*str = expand_wildcard(str, &lst);
	arr = split_list(lst, ' ');
	ft_lstclear(&lst, free);
	if (!arr || (ft_arrlen(arr) != 1 && *arr))
		return (ft_free("21", arr, *str), throw_error(REDIR, NULL, NULL), FALSE);
	return (TRUE);
}

int	open_file(t_redir *r, char **filename)
{
	r->fd = open(*filename, r->flag, 0644);
	if (r->fd < 0)
		return (perror(*filename), free(*filename), FALSE);
	if (r->mode == READ)
	{
		if (dup2(r->fd, STDIN) == -1)
			return (printfd(2, "minishell: %s", strerror(errno)), \
				close(r->fd), FALSE);
	}
	else
	{
		if (dup2(r->fd, STDOUT) == -1)
			return (printfd(2, "minishell: %s", strerror(errno)), \
				close(r->fd), FALSE);
	}
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
		if (expand_target(vars, &expanded) == FALSE)
			return (FALSE);
		if (r->mode == HEREDOC)
		{
			//
		}
		else
		{
			if (open_file(r, &expanded) == FALSE)
			{
				// close all open fds	
				return (FALSE);
			}
		}	
		free(expanded);
		tmp = tmp->next;
	}
	return (TRUE);
}
