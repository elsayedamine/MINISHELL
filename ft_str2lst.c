/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/05 01:07:27 by aelsayed         ###   ########.fr       */
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

void	ft_lstpop(t_list *head, t_list *pos, size_t n)
{
	t_list	*last;

	if (!pos || !head)
		return ;
	while (head && head->next != pos)
		head = head->next;
	if (head && head->next == pos)
	{
		head->next = get_node(head, n);
		last = ft_lstlast(pos);
		last->next = NULL;
		ft_lstclear(&pos, free);
	}
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

int	adjust(t_shell *vars, t_list *head, char *str, int i)
{
	int		len;
	char	*name;
	t_list	*var_value;

	len = get_var_len(str + 1);
	if (len == 0)
		return (1);
	name = ft_strndup(str + 1, len);
	ft_lstpop(head, get_node(head, i), len + 1);
	var_value = ft_str2lst(get_env(name, vars), 1);
	ft_lstinsert(var_value, get_node(head, i));
	ft_free("11", name, str);
	return (len + 1);
}

void	expand(t_shell *vars, char **str)
{
	t_list	*head;
	t_list *node;
	int		i;
	char	c;

	if (!ft_strchr(*str, '$'))
		return ;
	head = ft_str2lst(*str, 0);
	node = head;
	i = 0;
	while (node)
	{
		c = *(char *)node->content;
		if (c == '\'')
		{
			node = node->next;
			i++;
			while (node && *(char *)node->content != '\'')
			{
				node = node->next;
				i++;
			}
		}
		else if (c == '$')
			i += adjust(vars, head, ft_lst2str(get_node(head, i)), i);
		else
			i++;
		node = get_node(head, i);
	}
	free(*str);
	*str = ft_lst2str(head);
	ft_lstclear(&head, free);
	// here we need to add the new remove quotes li katchecki l flags li kaynin f nodes
}

// void	expand(t_shell *vars, char **str)
// {
// 	t_list	*head;
// 	int		i;

// 	if (!ft_strchr(*str, '$'))
// 		return ;
// 	head = ft_str2lst(*str, 0);
// 	i = 0;
// 	while ((*str)[i])
// 	{
// 		if ((*str)[i++] == '\'')
// 			while ((*str)[i] && (*str)[i++] != '\'');
// 		if ((*str)[i] == '$')
// 			i += adjust(vars, head, &(*str)[i], i);
// 	}
// 	free(*str);
// 	*str = ft_lst2str(head);
// 	ft_lstclear(&head, free);
// 	// here we need to add the new remove quotes li katchecki l flags li kaynin f nodes
// }


// so my idea is u will take the content of each node and then give it to the ft_str2lst
// yak ... so hatwli 3ndk linked list kola node fiha char 
// bach mnin tbghi t expandi hatmchi lwst linked list o tbda t appendi the true value of the $var fach tl9a dollar
// db dak $var li kayn f env hatakhdo brasso o t3tih nit l ft_str2lst yak 
// o bach hatlse9 dik list lkbira b list dial $var hia bl function talta
// sf mnin twli 3ndk linked list jdida 
// 3tiha l ft_lst2str bach trj3a string kima kan o redo l blasto fl content ....
// i hope tkon fhmti rah 7awlt nshel lik l work bach tched tkhdem b had l funtions easily

// hadchi kamel may7tajch 7it deja sawbt dik l fct f libft smitha ft_strinsert
// kat inserti lik string west string

// sa3a 3awdt tfkrt 3lach drna had lblan kamel hi 3la wed lflag dial kolla node bach n3rfo wach dak char wach asli wla ban mor l expantion 
// so yeah we need these linked list
