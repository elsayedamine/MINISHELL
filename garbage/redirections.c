/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 02:05:04 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/19 02:05:56 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int	join(t_list **tokens)
// {
// 	char	*new_content;
// 	char	*tmp_content;
// 	t_list	*to_delete;
// 	t_list	*tmp;

// 	tmp = *tokens;
// 	while (tmp && tmp->next)
// 	{
// 		tmp_content = (char *)tmp->content;
// 		if (!is_op(tmp_content) && !is_op((char *)tmp->next->content) && \
// 			!is_par(tmp_content) && !is_par((char *)tmp->next->content))
// 		{
// 			new_content = ft_strjoin(tmp_content, (char *)tmp->next->content);
// 			free(tmp->content);
// 			tmp->content = new_content;
// 			to_delete = tmp->next;
// 			tmp->next = tmp->next->next;
// 			ft_lstdelone(to_delete, free);
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// 	return (TRUE);
// }

// void	pop_space(t_list **s)
// {
// 	t_list	*new;
// 	t_list	*tmp;
// 	t_list	*next;
// 	t_list	*node;

// 	tmp = *s;
// 	new = NULL;
// 	while (tmp)
// 	{
// 		next = tmp->next;
// 		if (ft_iswhitespace(tmp->content) == FALSE)
// 		{
// 			node = ft_lstnew(ft_strdup(tmp->content));
// 			ft_lstadd_back(&new, node);
// 		}
// 		ft_free("1", tmp->content);
// 		free(tmp);
// 		tmp = next;
// 	}
// 	*s = new;
// }
