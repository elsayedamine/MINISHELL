/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:00:05 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/30 14:30:47 by ahakki           ###   ########.fr       */
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
	t_list	*tmp;

	tmp = vars->env;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, v, ft_strlen(v))\
			&& (((char *)tmp->content)[ft_strlen(v)] == '=' \
				|| ((char *)tmp->content)[ft_strlen(v)] == '\0') \
					&& ft_strlen(v) <= ft_strlen(av))
		{
			free(tmp->content);
			tmp->content = ft_strdup(av);
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
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
	t_list	*tmp;

	tmp = vars->env;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, v, ft_strlen(v)) &&
			((char *)tmp->content)[ft_strlen(v)] == '=')
		{
			old_val = ft_strdup((char *)tmp->content + ft_strlen(v) + 1);
			new_val = av + ft_strlen(v) + 2;
			appended = ft_strjoin(old_val, new_val);
			ft_free("11", old_val, tmp->content);
			tmp->content = ft_strjoin(v, "=");
			tmp->content = ft_strjoin_f(tmp->content, appended, 1);
			return ((void)ft_free("11", appended, v));
		}
		tmp = tmp->next;
	}
	new_val = av + ft_strlen(v) + 2;
	appended = ft_strjoin_f(ft_strjoin(v, "="), new_val, 1);
	ft_lstadd_back(&vars->env, ft_lstnew(appended));
	free(v);
}
void	ft_printexp(t_shell	*vars)
{
	t_list	*tmp;
	char	*new_str;
	char	*str;

	tmp = vars->env;
	while (tmp)
	{
		str = ft_strdup((char *)tmp->content);
		if (ft_strchr_index(str, '=') != -1)
		{
			new_str = ft_strinsert(str, "\"", ft_strchr_index(str, '=') + 1);
			ft_free("1", str);
			str = ft_strjoin_f(new_str, "\"", 1);
		}
		printf("declare -x %s\n", str);
		ft_free("1", str);
		tmp = tmp->next;
	}
}
int	ft_isvn(char *v, int flag, t_shell *vars)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = vars->env;
	if (!v || (!ft_isalpha(v[0]) && v[0] != '_'))
		return (FALSE);
	while (v && v[i])
	{
		if ((flag == 1 && ft_strchr("!@#$%^&*()-[]{}|\\:;\"'<>,.?/~` /", v[i])) ||
			(flag == 0 && ft_strchr("!@#$%^&*()-+=[]{}|\\:;\"'<>,.?/~` /", v[i])))
			return (FALSE);
		i++;
	}
	if (flag == 0)
	{
		while (tmp)
		{
			if (!ft_strncmp((char *)tmp->content, v, ft_strlen(v)) &&
				(((char *)tmp->content)[ft_strlen(v)] == '\0' || ((char *)tmp->content)[ft_strlen(v)] == '='))
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
		return (ft_printexp(vars), TRUE);
	while (i < ac)
	{
		v = var_name(av[i], '+');
		if (ft_isvn(v, 1, vars) && !ft_strncmp(av[i] + ft_strlen(v), "+=", 2))
		{
			ft_append(v, av[i++], vars);
			continue;
		}
		v = var_name(av[i], '=');
		if (ft_isvn(v, 1, vars) && !ft_strchr(v, '+'))
		{			
			ft_add(v, av[i++], vars);
			continue;
		}
		if (ft_isvn(av[i], 0, vars))
		{
			i++;
			continue;
		}
		printfd(2, "export: `%s': not a valid identifier\n", av[i++]);
		ft_free("1", v);
	}
	ft_free("2", vars->envp);
	vars->envp = ft_list2arr(vars->env);
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
