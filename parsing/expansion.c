/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/21 04:11:03 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_var_len(char *str)
{
	int	i;

	i = 0;
	if (!str || !(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

int	add_value(t_shell *vars, t_list **s, char *str, int q)
{
	char	*var_name;
	char	*var_value;

	var_value = NULL;
	var_name = NULL;
	if (*str == '$' && ft_strchr("'\"", *(str + 1)) && !q)
		return (1);
	if (*str == '$' && *(str + 1) == '?')
		var_value = ft_itoa(vars->exit);
	else if (get_var_len(str + 1) == 0)
		return (ft_lstadd_back(s, ft_lstnew(ft_strdup("$"))), 1);
	if (!var_value)
	{
		var_name = ft_strndup(str + 1, get_var_len(str + 1));
		var_value = ft_strdup(get_env(var_name, vars));
	}
	ft_lstadd_back(s, ft_str_to_lst(var_value, 1));
	return (ft_free("11", var_name, var_value), \
		get_var_len(str + 1) + 1 + (*str == '$' && str[1] == '?'));
}

void	handle_single_quotes(t_list **s, int *i, char *str)
{
	(*i) += append(s, '\'', 0);
	while (str[*i] && str[*i] != '\'')
		*i += append(s, str[*i], 0);
	if (str[*i] == '\'')
		*i += append(s, '\'', 0);
}

t_list	*breakdown(t_shell *vars, char **str)
{
	int		i;
	int		q;
	t_list	*s;

	s = NULL;
	ft_init(2, &i, &q);
	while (*str && (*str)[i])
	{
		if ((*str)[i] == '"')
		{
			q = !q;
			i += append(&s, (*str)[i], 0);
		}
		else if ((*str)[i] == '\'' && !q)
			handle_single_quotes(&s, &i, *str);
		else if ((*str)[i] == '$')
			i += add_value(vars, &s, &(*str)[i], q);
		else
			i += append(&s, (*str)[i], 0);
	}
	return (s);
}

void	expand(t_shell *vars, char **str, char ***arr)
{
	t_list	*lst;

	lst = breakdown(vars, str);
	ft_free("1", *str);
	*str = ft_lst2str(lst);
	*str = expand_wildcard(str, &lst);
	ft_free("2", *arr);
	*arr = split_list(lst, ' ');
	ft_lstclear(&lst, free);
}
