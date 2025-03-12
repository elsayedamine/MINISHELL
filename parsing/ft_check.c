/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:30:19 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/12 09:39:05 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

void	pop_spaces(t_list *lst)
{
	t_list	*next;
	t_list	*prev;

	t_list (*tmp) = lst;
	prev = NULL;
	while (tmp)
	{
		if (ft_iswhitespace((char *)tmp->content))
		{
			next = tmp->next;
			ft_lstdelone(tmp, free);
			if (prev)
				prev->next = next;
			else
				lst = next;
			tmp = next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

int	ft_check(void)
{
	int	valid;

	valid = 0;
	valid += isvalid_quotes();
	valid += isvalid_op();
	valid += isvalid_par();
	valid += ft_nodejoin();
	if (valid != 4)
		return (FALSE);
	pop_spaces(g_vars.args);
	return (TRUE);
}
