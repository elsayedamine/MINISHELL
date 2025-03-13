/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:30:19 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/13 03:20:19 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

// Helper function to check if an entire string is whitespace
// bool	ft_str_is_whitespace(const char *s)
// {
// 	while (*s)
// 	{
// 		if (!ft_iswhitespace(*s)) // Assuming ft_iswhitespace checks for " \t\n\v\f\r"
// 			return (false);
// 		s++;
// 	}
// 	return (true);
// }

void	pop_spaces(t_list **lst)
{
	t_list	*next;

	if (!lst || !*lst)
		return;

	if (ft_iswhitespace((char *)(*lst)->content))
	{
		next = (*lst)->next;    // Store the next node
		ft_lstdelone(*lst, free);  // Free the current node
		*lst = next;    // Move the head forward
		pop_spaces(lst);  // Recurse on the new head
	}
	else
		pop_spaces(&(*lst)->next);  // Recurse on the next node
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
	g_vars.tmp = g_vars.args;
	// pop_spaces(&g_vars.args);
	// ft_lstiter(g_vars.tmp, printf);
	// exit(0);
	return (TRUE);
}
