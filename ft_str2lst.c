/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/05 22:31:46 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_str2lst(char *str, int flag)
{
	int		i;
	t_list	*node;

	i = 0;
	node = NULL;
	while (str && str[i])
	{
		ft_lstadd_back(&node, ft_lstnew(ft_strndup(&str[i++], 1)));
		node->type = flag;
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

	if (pos && !pos->next)
	{
		pos->next = insert;
		return ;
	}
	if (!insert || !pos)
		return ;
	next = pos->next;
	pos->next = insert;
	last = ft_lstlast(insert);
	last->next = next;
}

t_list	*get_node(t_list *lst, size_t pos)
{
	while (lst && pos--)
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

// char	*expand(t_shell *vars, t_list *head)
// {
// 	t_list	*node;
// 	int		i;
// 	char	c;
// 	char	q;

// 	ft_init(3, &i, &c, &q);
// 	while (node)
// 	{
// 		c = *(char *)node->content;
// 		if (c == '"')
// 			q = !q;
// 		if (c == '\'' && !q)
// 		{
// 			node = node->next;
// 			while (node && *(char *)node->content != '\'' && i++)
// 				node = node->next;
// 		}
// 		if (c == '$')
// 		{
// 			// my idea is to insert all the expansions till end then pop the var names
// 		}
// 		else
// 			node = node->next;
// 	}
// 	return (ft_lst2str(node));
// }

void	ft_lstpop(t_list *node, size_t n)
{
	t_list	*next;
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

int main(int ac, char **av)
{
	if (ac > 1)
	{
		t_list *node = ft_str2lst(av[1], 0);
		t_list *node2 = ft_str2lst(av[2], 1);
		ft_lstpop(get_node(node, 100), 5);
		ft_lstiter(get_node(node, 100), printf);
		ft_lstinsert(node2, get_node(node, 100));
		printf("%s\n", ft_lst2str(node));
	}
}
