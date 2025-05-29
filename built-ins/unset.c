/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 18:09:58 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	unset_variable(char *key, t_shell *vars)
{
	t_list	*curr;
	t_list	*next;
	char	*content;
	t_list	*new_env;

	new_env = NULL;
	curr = vars->env;
	if (!ft_isvn(key, 1, vars))
		return (TRUE);
	while (curr)
	{
		next = curr->next;
		content = (char *)curr->content;
		if (!(!ft_strncmp(content, key, ft_strlen(key)) \
			&& (content[ft_strlen(key)] == '=' || !content[ft_strlen(key)])))
		{
			curr->next = NULL;
			ft_lstadd_back(&new_env, curr);
		}
		curr = next;
	}
	vars->envp = ft_list2arr(new_env);
	return (TRUE);
}

int	unset(int ac, char **av, t_shell *vars)
{
	int	i;

	i = 1;
	(void)ac;
	while (av[i])
	{
		unset_variable(av[i], vars);
		i++;
	}
	return (EXIT_SUCCESS);
}
// int main (int ac, char **av, char **envp)
// {
	// t_shell vars;
	// vars.envp = ft_arrdup(envp);
	// unset(ac, av, &vars);
	// env(1, av, &vars);
	// return (0);
// }
