/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 21:35:39 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/07 19:06:03 by aelsayed         ###   ########.fr       */
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

int	add_value(t_shell *vars, t_list **s, char *str)
{
	int		len;
	char	*var_name;
	char	*var_value;
	t_list	*last;

	var_value = NULL;
	var_name = NULL;
	len = get_var_len(str + 1);
	if (*str == '$' && *(str + 1) == '?')
		var_value = ft_itoa(vars->exit);
	else if (len == 0)
		return (ft_lstadd_back(s, ft_lstnew(ft_strdup("$"))), 1);
	if (!var_value)
	{
		var_name = ft_strndup(str + 1, len);
		var_value = ft_strdup(get_env(var_name, vars));
	}
	last = ft_lstlast(*s);
	if (last)
		last->next = ft_str_to_lst(var_value, 1);
	else
		*s = ft_str_to_lst(var_value, 1);
	ft_free("11", var_name, var_value);
	return (len + 1 + (*str == '$' && str[1] == '?'));
}

int	add_char(t_list **s, char c)
{
	t_list	*new;

	new = ft_lstnew(ft_strndup(&c, 1));
	new->type = 0;
	ft_lstadd_back(s, new);
	return (1);
}

void	handle_single_quotes(t_list **s, int *i, char *str)
{
	(*i) += add_char(s, '\'');
	while (str[*i] && str[*i] != '\'')
		*i += add_char(s, str[*i]);
	if (str[*i] == '\'')
		*i += add_char(s, '\'');
}

void	expand(t_shell *vars, char **str, char ***arr)
{
	int 	i;
	int		q;
	t_list	*s;

	s = NULL;
	ft_init(2, &i, &q);
	while ((*str)[i])
	{
		if ((*str)[i] == '"')
		{
			q = !q;
			i += add_char(&s, (*str)[i]);
		}
		else if ((*str)[i] == '\'' && !q)
			handle_single_quotes(&s, &i, *str);
		else if ((*str)[i] == '$')
			i += add_value(vars, &s, &(*str)[i]);
		else
			i += add_char(&s, (*str)[i]);
	}
	ft_free("12", *str, *arr);
	*str = ft_lst2str(s);
	*arr = split_list(s, ' ');
	ft_lstclear(&s, free);
}
