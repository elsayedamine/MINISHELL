/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:26:09 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 00:08:34 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_files(t_shell *vars)
{
	t_redir	*r;
	t_list	*redir;
	int		fd;
	char	*exp;

	redir = vars->redir;
	while (redir)
	{
		r = (t_redir *)redir->content;
		exp = alloc(0, ft_strdup(r->target), 0);
		if (expand_target(vars, &exp) == FALSE)
			return (FALSE);
		fd = open(r->target, r->flag, 0644);
		if (fd == -1)
			return (perror(r->target), g_var->exit_status = errno, FALSE);
		close(fd);
		redir = redir->next;
	}
	return (TRUE);
}

int	*apply_redirect_shell(t_shell *vars)
{
	t_redir	*r;
	t_list	*tmp;
	char	*expanded;

	vars->fds[0] = dup(STDIN);
	vars->fds[1] = dup(STDOUT);
	if (vars->fds[0] == -1 || vars->fds[1] == -1)
		return (perror("dup"), NULL);
	tmp = vars->redir;
	while (tmp)
	{
		r = (t_redir *)tmp->content;
		expanded = alloc(0, ft_strdup(r->target), 0);
		if (r->mode != HEREDOC && expand_target(vars, &expanded) == FALSE)
			return (perform_dups(vars->fds[0], vars->fds[1]), \
				vars->fds = NULL, NULL);
		if (open_file(r, &expanded) == FALSE)
			return (g_var->exit_status = 1, \
					perform_dups(vars->fds[0], vars->fds[1]), \
						vars->fds = NULL, NULL);
		tmp = tmp->next;
	}
	return (vars->fds);
}

int	*redirect_sub(t_shell *vars, t_list **ast, t_list *node)
{
	t_list	*s;
	int		*fds;

	fds = (int *)alloc(sizeof(int) * 4, NULL, 'M');
	if (!fds)
		return (NULL);
	fds[0] = -1;
	fds[1] = -1;
	fds[2] = dup(0);
	fds[3] = dup(1);
	vars->fds = fds;
	if (!node || (node->type != SUBSHELL && !node->next))
		return (fds);
	if (node->next && node->next->type == CMD && \
		is_there_red(node->next->content))
	{
		s = tokenize_command(node->next->content);
		vars->redir = create_redir_list(vars, &s);
		apply_redirect_shell(vars);
		if (vars->fds == NULL)
		{
			g_var->exit_status = 1;
			return (skip(ast, AND), NULL);
		}
	}
	return (fds);
}

void	return_original_std(t_shell *vars)
{
	if (vars->fds)
	{
		if (vars->fds[2] != -1)
			dup2(vars->fds[2], 0);
		if (vars->fds[3] != -1)
			dup2(vars->fds[3], 1);
		// close(vars->fds[0]);
		// close(vars->fds[1]);
		close(vars->fds[2]);
		close(vars->fds[3]);
	}
}
