/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:58:10 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/13 19:08:35 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*removequotes(char *str, t_list	*s)
{
	char	*result;
	int		i;
	int		j;
	int		c;

	if (!str || !(*str))
		return (NULL);
	if (ft_count_char(str, '\'') == 0 && ft_count_char(str, '"') == 0)
		return (str);
	result = (char *)malloc(ft_strlen(str) + 1);
	if (!result)
		return (free(str), NULL);
	ft_init(3, &i, &j, &c);
	while (str[i])
	{
		if (!ft_lstgetnode(s, i)->type && \
			(str[i] == '\'' || str[i] == '"') && !c)
			c = str[i];
		else if (!ft_lstgetnode(s, i)->type && str[i] == c)
			c = 0;
		else
			result[j++] = str[i];
		i++;
	}
	return (result[j] = '\0', free(str), result);
}

t_list	*remove_quotes_from_list(t_list *lst)
{
	t_list	*curr;
	t_list	*new_lst;
	char	quote;
	char	*c;

	curr = lst;
	new_lst = NULL;
	quote = 0;
	while (curr)
	{
		c = (char *)curr->content;
		if (!curr->type && (*c == '"' || *c == '\'') && !quote)
			quote = *c;
		else if (!curr->type && *c == quote)
			quote = 0;
		else
			ft_lstadd_back(&new_lst, ft_lstnew(ft_strdup(c)));
		curr = curr->next;
	}
	return (ft_lstclear(&lst, free), new_lst);
}

// char	**removequotes_arr(char **arr)
// {
// 	int		i;

// 	if (!arr)
// 		return (NULL);
// 	i = 0;
// 	while (arr[i])
// 	{
// 		arr[i] = removequotes(arr[i]);
// 		i++;
// 	}
// 	return (arr);
// }

t_list	*ft_str_to_lst(char *str, int flag)
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
