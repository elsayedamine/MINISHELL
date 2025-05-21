/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:18:51 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/21 06:46:17 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir	*create_redir_node(t_type mode, char *target)
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

t_list	*create_redir_list(t_list **s)
{
	t_list	*raw;
	t_list	*tmp;
	t_list	*redir;

	tmp = *s;
	redir = NULL;
	raw = NULL;
	while (tmp)
	{
		if (tmp->type >= READ && tmp->next)
		{
			ft_lstadd_back(&redir, ft_lstnew(create_redir_node(tmp->type, \
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

int	add_token(char *str, t_list **lst)
{
	int		i;
	char	q;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			q = str[i++];
			while (str[i] && str[i] != q)
				i++;
			if (str[i] == q)
				i++;
		}
		else if (ft_strchr(WHITE, str[i]) || str[i] == '<' || str[i] == '>')
			break ;
		else
			i++;
	}
	ft_lstadd_back(lst, create_node(ft_strndup(str, i)));
	return (i);
}

t_list	*tokenize_command(char *cmd)
{
	int		i;
	t_list	*lst;

	lst = NULL;
	i = 0;
	while (cmd[i])
	{
		while (ft_strchr(WHITE, cmd[i]) && cmd[i])
			i++;
		if (cmd[i] == '\'' || cmd[i] == '"')
			i += add_token(cmd + i, &lst);
		else if ((!ft_strncmp(&cmd[i], "<<", 2) \
			|| !ft_strncmp(&cmd[i], ">>", 2)))
		{
			ft_lstadd_back(&lst, create_node(ft_strndup(cmd + i, 2)));
			i += 2;
		}
		else if (cmd[i] == '<' || cmd[i] == '>')
			ft_lstadd_back(&lst, create_node(ft_strndup(&cmd[i++], 1)));
		else if (cmd[i])
			i += add_token(cmd + i, &lst);
	}
	return (lst);
}

void	extract_redirections(t_shell *vars, char **original)
{
	int		i;
	int		q;
	t_list	*s;
	char	**arr;

	if (!original || !*original)
	{
		vars->redir = NULL;
		return ;
	}
	ft_init(2, &q, &i);
	s = tokenize_command(*original);
	vars->redir = create_redir_list(&s);
	free(*original);
	arr = ft_list2arr(s);
	*original = ft_arr2str(arr, ' ');
	ft_free("2", arr);
}
