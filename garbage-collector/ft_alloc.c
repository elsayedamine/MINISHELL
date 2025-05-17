/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:49:07 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/15 15:26:18 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    *ft_alloc(size_t size, void *ptr, char c)
{
    static t_malloc    *head;
    t_malloc        *new_node;

    if (ptr)
    {
        ft_lst_add_back(&head, (t_malloc *)ptr);
        return (ptr);
    }
    else if (c == 'M')
    {
        new_node = ft_lst_new(size);
        if (!new_node)
            return (NULL);
        ft_lst_add_back(&head, new_node);
        return (new_node->ptr);
    }
    else if (c == 'F')
        free_all_memory(&head);
    return (NULL);
}

void    *ft_malloc2(size_t size)
{
    return (ft_alloc(size, NULL, 'M'));
}

void    ft_exit2(int status)
{
    ft_alloc(0, NULL, 'F');
    exit(status);
}