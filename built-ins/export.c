/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/24 22:33:13 by aelsayed         ###   ########.fr       */
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
	var = (char *)alloc(sizeof(char) * (i + 1), NULL, 'M');
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
		ft_lstadd_back(&vars->env, \
			alloc(0, ft_lstnew(alloc(0, ft_strdup(av), 0)), 0));
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
		ft_lstadd_back(&vars->env, \
			alloc(0, ft_lstnew(alloc(0, ft_strdup(v), 0)), 0));
	}
	return (TRUE);
}

void	export_failed(char *str, t_shell *vars)
{
	(void)vars;
	g_var->exit_status = 1;
	printfd(2, "export: `%s': not a valid identifier\n", str);
	return ;
}

int	export(int ac, char **av, t_shell *vars)
{
	char	*v;
	int		i;

	i = 1;
	if (ac == 1)
		return (ft_printexport(vars), EXIT_SUCCESS);
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
			export_failed(av[1], vars);
		i++;
	}
	vars->envp = ft_list2arr(vars->env);
	return (g_var->exit_status);
}
