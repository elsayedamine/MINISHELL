/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/23 23:00:05 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_name(char *s, char flag)
{
	int	i;
	char *var;

	i = 0;
	while (s[i] && s[i] != flag)
		i++;
	if (s[i] != flag)
		return (NULL);
	var = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != flag)
	{
		var[i] = s[i];
		i++;
	}
	var[i] = '\0';
	return (var);
}

void	ft_add(char *v, char *av, t_shell *vars)
{
	vars->tmp = vars->env;
	while (vars->tmp)
	{
		if (ft_strncmp((char *)vars->tmp->content, v, ft_strlen(v)) == 0 \
			&& ((char *)vars->tmp->content)[ft_strlen(v)] == '=' \
				&& ft_strlen(v) <= ft_strlen(av))
		{
			free(vars->tmp->content);
			vars->tmp->content = ft_strdup(av);
			break;
		}
		vars->tmp = vars->tmp->next;
	}
	if (!vars->tmp)
		ft_lstadd_back(&vars->env, ft_lstnew(ft_strdup(av)));
	free(v);
}

char	*ft_strjoin_f(char *s1, char *s2, int free_s)
{
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = ft_strjoin(s1, s2);
	if (free_s == 1)
		free(s1);
	if (free_s == 2)
		free(s2);
	return (res);
}

void	ft_append(char *v, char *av, t_shell *vars)
{
	char	*new_val;
	char	*old_val;
	char	*appended;

	if (ft_strncmp(av + ft_strlen(v), "+=", 2) != 0)
		return (free(v));
	vars->tmp = vars->env;
	while (vars->tmp)
	{
		if (ft_strncmp((char *)vars->tmp->content, v, ft_strlen(v)) == 0 &&
			((char *)vars->tmp->content)[ft_strlen(v)] == '=')
		{
			old_val = ft_strdup((char *)vars->tmp->content + ft_strlen(v) + 1);
			new_val = av + ft_strlen(v) + 2;
			appended = ft_strjoin(old_val, new_val);
			ft_free("11", old_val, vars->tmp->content);
			vars->tmp->content = ft_strjoin(v, "=");
			vars->tmp->content = ft_strjoin_f(vars->tmp->content, appended, 1);
			return ((void)ft_free("11", appended, v));
		}
		vars->tmp = vars->tmp->next;
	}
	free(v);
}

int	export(int ac, char **av, t_shell *vars)
{
	char	*v;
	int		i;

	i = 1;
	while (i < ac)
	{
		v = var_name(av[i], '+');
		if (v && ft_strncmp(av[i] + ft_strlen(v), "+=", 2) == 0)
		{
			ft_append(v, av[i], vars);
			i++;
			continue;
		}
		v = var_name(av[i], '=');
		if (v && !ft_strchr(v, '+'))
		{
			ft_add(v, av[i], vars);
			i++;
			continue;
		}
		printfd(2, "export: `%s': not a valid identifier\n", av[i]);
		ft_free("1", v);
		i++;
	}
	return (TRUE);
}

// int main(int ac, char **av, char **envp)
// {
// 	t_shell vars;

// 	vars.env = ft_arr2list(envp);
// 	// ft_lstiter(vars.env, printf);
// 	printf("before---------------------------------------------------------------------\n");
// 	export(ac, av, &vars);
// 	printf("after---------------------------------------------------------------------\n");
// 	ft_lstiter(vars.env, printf);
// 	return (0);
// }
