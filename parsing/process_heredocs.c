/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 10:29:37 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/24 19:09:00 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_heredoc_line(t_shell *vars, char **str)
{
	char	*s;
	int		i;
	int		q;
	t_list	*lst;

	s = *str;
	ft_init(2, &i, &q);
	lst = NULL;
	while (s && s[i])
	{
		if (s[i] == '$')
			i += extract_var_value(vars, &lst, &s[i], 0);
		else
			ft_lstadd_back(&lst, ft_lstnew(ft_strndup(&s[i++], 1)));
	}
	free(*str);
	return (ft_lst2str(lst));
}

void	fill_heredoc(t_shell *vars, t_redir **r)
{
	char	*line;
	pid_t	pid;
	int		status;
	
	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
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
		free(line);
		close((*r)->fd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_var->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			g_var->exit_status = 128 + WTERMSIG(status);
			write(1, "\n", 1);
			*r = NULL;
		}
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
	return (ft_substr(str, start, i - start));
}

t_redir	*heredoc_node(t_shell *vars, char *target)
{
	static int	n = 0;
	t_redir		*r;

	r = (t_redir *)malloc(sizeof(t_redir));
	if (!r)
		return (NULL);
	r->mode = HEREDOC;
	r->delim = old_removequotes(extract_raw_heredoc_delim(target));
	r->flag = O_RDONLY;
	r->target = ft_strjoin_f("/tmp/minishell", ft_itoa(n++), 2);
	r->q = ft_strchr(target, '\'') || ft_strchr(target, '"');
	r->fd = open(r->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (r->fd == -1)
		return (perror("heredoc opening failed"), free(r), NULL);
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
			// free_all_rdir_list
			ft_lstadd_back(&heredocs, ft_lstnew(flag));
		}
		vars->tmp = vars->tmp->next;
	}
	vars->heredoc = heredocs;
	return (TRUE);
}
