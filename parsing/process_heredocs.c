/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:29:37 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/31 02:47:51 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_doc_line(t_shell *vars, t_redir **r)
{
	char	*line;

	signal(SIGINT, clear);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, (*r)->delim))
			break ;
		if (!(*r)->q)
			line = expand_heredoc_line(vars, &line);
		printfd((*r)->fd, "%s\n", line);
		free(line);
	}
	if (!line)
		throw_error(EOOF, (*r)->delim, &vars->bash_line_counter);
	free(line);
	alloc(0, NULL, 'F');
}

void	fill_heredoc(t_shell *vars, t_redir **r)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		read_doc_line(vars, r);
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		signal(SIGINT, foo);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			write(1, "\n", 1);
			*r = NULL;
		}
		g_var->exit_status = WEXITSTATUS(status);
	}
}

char	*extract_raw_heredoc_delim(char *str)
{
	int		i;
	int		start;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	start = i;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '"'))
			quote = str[i];
		else if (quote && str[i] == quote)
			quote = 0;
		else if (!quote && (ft_isspace(str[i]) || ft_strchr("|&<>()", str[i])))
			break ;
		i++;
	}
	return (alloc(0, ft_substr(str, start, i - start), 0));
}

t_redir	*heredoc_node(t_shell *vars, char *target)
{
	static int	n = 0;
	t_redir		*r;

	r = (t_redir *)alloc(sizeof(t_redir), NULL, 'M');
	if (!r)
		return (NULL);
	r->mode = HEREDOC;
	r->delim = old_removequotes(extract_raw_heredoc_delim(target));
	r->flag = O_RDONLY;
	r->target = ft_strjoin_f("/tmp/minishell", ft_itoa(n++), 2);
	alloc(0, r->target, 0);
	r->q = ft_strchr(target, '\'') || ft_strchr(target, '"');
	r->fd = open(r->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (r->fd == -1)
		return (perror("heredoc opening failed"), NULL);
	fill_heredoc(vars, &r);
	return (r);
}

int	process_heredocs(t_shell *vars)
{
	t_list	*heredocs;
	t_redir	*flag;

	heredocs = NULL;
	vars->tmp = vars->args;
	while (vars->tmp)
	{
		if (!ft_strcmp(vars->tmp->content, "<<") && vars->tmp->next)
		{
			flag = heredoc_node(vars, vars->tmp->next->content);
			if (!flag)
				return (FALSE);
			ft_lstadd_back(&heredocs, alloc(0, ft_lstnew(flag), 0));
		}
		vars->tmp = vars->tmp->next;
	}
	vars->hd = heredocs;
	vars->heredoc = heredocs;
	return (TRUE);
}
