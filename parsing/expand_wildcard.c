/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:18:12 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/25 13:50:27 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_quotes(char *quote, char c, char sep, int type)
{
	if (!type && c == *quote && *quote)
		*quote = 0;
	else if (!type && (c == '\'' || c == '"') && !*quote)
		*quote = c;
	else if (!*quote && c == sep)
		return (TRUE);
	return (FALSE);
}

int	*extract_pattern(char *str, int index, char sep, t_list *s)
{
	int		*borders;
	char	quote;

	borders = (int *)alloc(sizeof(int) * 2, NULL, 'M');
	if (!str || index < 0 || index >= (int)ft_strlen(str) || !borders)
		return (NULL);
	quote = 0;
	borders[0] = index;
	borders[1] = index;
	while (borders[0] > 0)
	{
		if (handle_quotes(&quote, str[borders[0] - 1], sep, \
			ft_lstgetnode(s, borders[0] - 1)->type))
			break ;
		borders[0]--;
	}
	while (str[borders[1]])
	{
		if (handle_quotes(&quote, str[borders[1]], sep, \
			ft_lstgetnode(s, borders[1])->type))
			break ;
		borders[1]++;
	}
	return (borders);
}

int	extract_wildcard(char *str, t_list **new, int index, t_list *s)
{
	int		*bords;
	char	**arr;
	char	*pattern;
	int		diff;
	t_list	*node;

	bords = extract_pattern(str, index, ' ', s);
	if (!bords)
		return (0);
	pattern = removequotes(alloc(0, \
		ft_substr(str, bords[0], bords[1] - bords[0]), 0), s);
	arr = wildcard(pattern);
	if (arr)
	{
		node = ft_lstgetnode(*new, bords[0] - 1);
		while (node && node->next)
			node->next = node->next->next; // maybe could be an error
		pattern = ft_arr2str(arr, ' ');
	}
	else
		pattern = ft_substr(str, bords[0], bords[1] - bords[0]);
	ft_lstadd_back(new, ft_str_to_lst(alloc(0, pattern, 0), 1));
	diff = bords[1] - index;
	return (diff);
}

int	canbexpanded(char *str, int i)
{
	if (!ft_strncmp(str, "export ", 7))
	{
		while (i > 0 && str[i] != ' ' && str[i] != '=')
			i--;
		if (str[i] == '=')
			return (FALSE);
	}
	return (TRUE);
}

char	*expand_wildcard(char **str, t_list **old)
{
	int		i;
	char	q;
	char	*new_str;
	t_list	*new;

	i = 0;
	q = 0;
	new = NULL;
	while ((*str)[i])
	{
		if (!ft_lstgetnode(*old, i)->type && \
			((*str)[i] == '"' || (*str)[i] == '\''))
		{
			handle_quotes(&q, (*str)[i], 0, 0);
			i += append(&new, (*str)[i], 0);
		}
		else if (!q && (*str)[i] == '*' && canbexpanded(*str, i))
			i += extract_wildcard(*str, &new, i, *old);
		else
			i += append(&new, (*str)[i], ft_lstgetnode(*old, i)->type);
	}
	new_str = alloc(0, ft_lst2str(new), 0);
	*old = new;
	return (new_str);
}
