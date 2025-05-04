/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/04 22:23:46 by aelsayed         ###   ########.fr       */
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

t_list	*ft_lstinsert(t_list *base, t_list *insert, t_list *pos)
{
	t_list	*new;
	t_list	*curr;

	new = NULL;
	curr = base;
	while (curr && curr != pos)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(curr->content)));
		curr = curr->next;
	}
	if (curr != pos)
		return (ft_lstclear(&new, free), base);
	while (insert)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(insert->content)));		
		insert = insert->next;
	}
	while (curr)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_strdup(curr->content)));
		curr = curr->next;
	}
	return (new);
}

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
