/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/06 21:40:26 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_str2lst(char *str, int flag)
{
	int		i;
	t_list	*node;
	t_list	*new;

	i = 0;
	node = NULL;
	while (str && str[i])
	{
		new = ft_lstnew(ft_strndup(&str[i++], 1));
		new->type = flag;
		ft_lstadd_back(&node, new);

	}
	return (node);
}

char	*ft_lst2str(t_list	*node)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = ft_lstsize(node);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len && node && node->content)
	{
		str[i++] = *(char *)node->content;
		node = node->next;
	}
	str[i] = '\0';
	return (str);
}

void	ft_lstinsert(t_list *insert, t_list *pos)
{
	t_list	*last;
	t_list	*next;

	if (!insert)
		return ;
	if (pos && !pos->next)
	{
		pos->next = insert;
		return ;
	}
	next = pos->next;
	pos->next = insert;
	last = ft_lstlast(insert);
	if (last)
		last->next = next;
}

t_list	*get_node(t_list *lst, size_t pos)
{
	while (lst && lst->next && pos--)
		lst = lst->next;
	return (lst);
}

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

void	ft_lstpop(t_list *node, size_t n)
{
	t_list	*head;
	t_list	*tmp;

	if (!node || !node->next)
		return ;
	head = node;
	node = node->next;
	tmp = NULL;
	while (node && n--)
	{
		tmp = node->next;
		free(node->content);
		free(node);
		node = tmp;
	}
	head->next = node;
}

int	fetch_value(t_shell *vars, t_list **node)
{
	char	*var_name;
	int		len;
	char	*str;
	t_list	*var_value;
	t_list	*next;

	str = ft_lst2str((*node)->next);
	len = get_var_len(str + 1);
	var_name = ft_strndup(str + 1, len);
	var_value = ft_str2lst(get_env(var_name, vars), 1);
	ft_lstpop(*node, len + 1);
	next = (*node)->next;
	ft_lstinsert(var_value, *node);
	*node = next;
	len = ft_strlen(get_env(var_name, vars));
	return (ft_free("11", str, var_name), len + 2);
}

int	fetch_fst_value(t_shell *vars, t_list **node)
{
	int		i;
	t_list	*save;
	
	ft_lstadd_front(node, ft_lstnew("tmp"));
	save = (*node);
	i = fetch_value(vars, node);
	free(save);
	return (i);
}

// void	expand(t_shell *vars, char **str)
// {
	// t_list	*s;
	// t_list	*head;
	// int		c;
	// int		q;
	// int		i;
// 
	// if (!ft_strchr(*str, '$'))
		// return ;
	// s = ft_str2lst(*str, 0);
	// ft_init(3, &q, &i, &c);
	// head = s;
	// while (s)
	// {
		// c = *(char *)s->content;
		// if (c == '"')
			// q = !q;
		// else if (c == '\'' && !q)
		// {
			// i++;
			// s = s->next;
			// while (s && *(char *)s->content != '\'' && i++)
				// s = s->next;
		// }
		// if (i == 0 && c == '$')
			// i += fetch_fst_value(vars, &s);
		// if (s->next && *(char *)s->next->content == '$')
			// i += fetch_value(vars, &s);
		// else
		// {
			// i++;
			// s = s->next;
		// }
	// }
	// free(*str);
	// *str = ft_lst2str(head);
	// ft_lstclear(&head, free);
// }

int	add_value(t_shell *vars, t_list **s, char *str)
{
	int		len;
	char	*var_name;
	char	*var_value;
	t_list	*last;

	len = get_var_len(str + 1);
	if (len == 0)
		return (ft_lstadd_back(s, ft_lstnew(ft_strdup("$"))), 1);
	var_name = ft_strndup(str + 1, len);
	var_value = get_env(var_name, vars);
	last = ft_lstlast(*s);
	if (last)
		last->next = ft_str2lst(var_value, 1);
	else
		*s = ft_str2lst(var_value, 1);
	ft_free("1", var_name);
	return (len + 1);
}

int	add_char(t_list **s, char c)
{
	t_list	*new;

	new = ft_lstnew(ft_strndup(&c, 1));
	new->type = 0;
	ft_lstadd_back(s, new);
	return (1);
}

void	handle_single_quotes(t_list **s, int *i, char *str)
{
	(*i) += add_char(s, '\'');
	while (str[*i] && str[*i] != '\'')
		*i += add_char(s, str[*i]);
	if (str[*i] == '\'')
		*i += add_char(s, '\'');
}

void	expand(t_shell *vars, char **str)
{
	int 	i;
	int		q;
	t_list	*s;

	ft_init(2, &i, &q);
	s = NULL;
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
		{
			q = !q;
			i++;
		}
		if ((*str)[i] == '\'' && !q)
			handle_single_quotes(&s, &i, *str);
		if ((*str)[i] == '$')
			i += add_value(vars, &s, &(*str)[i]);
		else
			i += add_char(&s, (*str)[i]);
	}
	free(*str);
	*str = ft_lst2str(s);
	ft_lstclear(&s, free);
}
