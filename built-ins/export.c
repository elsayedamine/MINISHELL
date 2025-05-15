/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/15 11:27:41 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_name(char *s)
{
	int		i;
	char	*var;

	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
		i++;
	if (s[i] != '+' && s[i] != '=')
		return (NULL);
	var = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] && s[i] != '+' && s[i] != '=')
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

void	ft_add(char *v, char *av, t_shell *vars)
{
	t_list	*tmp;

	tmp = vars->env;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, v, ft_strlen(v)) \
			&& (((char *)tmp->content)[ft_strlen(v)] == '=' \
				|| ((char *)tmp->content)[ft_strlen(v)] == '\0') \
					&& ft_strlen(v) <= ft_strlen(av))
		{
			free(tmp->content);
			tmp->content = ft_strdup(av);
			break ;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		ft_lstadd_back(&vars->env, ft_lstnew(ft_strdup(av)));
	free(v);
}

int	ft_isvn(char *v, int flag, t_shell *vars)
{
	int		i;
	t_list	*tmp;

	i = -1;
	tmp = vars->env;
	if (!v || (!ft_isalpha(v[0]) && v[0] != '_'))
		return (FALSE);
	while (v[++i])
		if (!ft_isalnum(v[i]) && v[i] != '_')
			return (FALSE);
	if (flag == 0)
	{
		while (tmp)
		{
			if (!ft_strncmp((char *)tmp->content, v, ft_strlen(v)) \
				&& (((char *)tmp->content)[ft_strlen(v)] == '\0' \
					|| ((char *)tmp->content)[ft_strlen(v)] == '='))
				return (TRUE);
			tmp = tmp->next;
		}
		ft_lstadd_back(&vars->env, ft_lstnew(ft_strdup(v)));
	}
	return (TRUE);
}

int	export(int ac, char **av, t_shell *vars)
{
	char	*v;
	int		i;

	i = 1;
	if (ac == 1)
		return (ft_printexport(vars), TRUE);
	while (i < ac)
	{
		v = var_name(av[i]);
		if (ft_isvn(v, 1, vars) && !ft_strncmp(av[i] + ft_strlen(v), "+=", 2))
			append_value(v, av[i], vars);
		else if (ft_isvn(v, 1, vars) && !ft_strchr(v, '+'))
			ft_add(v, av[i], vars);
		else if (ft_isvn(av[i], 0, vars) && i++)
			continue ;
		else
		{
			printfd(2, "export: `%s': not a valid identifier\n", av[i]);
			ft_free("1", v);
		}
		i++;
	}
	ft_free("2", vars->envp);
	vars->envp = ft_list2arr(vars->env);
	return (TRUE);
}
