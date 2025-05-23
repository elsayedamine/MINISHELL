/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:14:29 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/23 18:46:31 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (free_s == 3)
		ft_free("11", s1, s2);
	return (res);
}

void	ft_printexport(t_shell	*vars)
{
	t_list	*tmp;
	char	*new_str;
	char	*str;

	tmp = vars->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "_=", 2))
		{
			tmp = tmp->next;
			continue ;
		}
		str = ft_strdup(tmp->content);
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

void	append_value(char *v, char *av, t_shell *vars)
{
	char	*new_val;
	char	*old_val;
	char	*appended;
	t_list	*tmp;

	tmp = vars->env;
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, v, ft_strlen(v)) \
			&& ((char *)tmp->content)[ft_strlen(v)] == '=')
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
