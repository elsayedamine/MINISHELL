/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:49:00 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/13 03:20:48 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_vars;

static int	_words(char const *s, char b)
{
	int	cnt;
	int	i;
	int	in_quotes;

	cnt = 0;
	i = 0;
	in_quotes = 0;

	while (s[i])
	{
		while (s[i] == b && !in_quotes)
			i++;
		if (s[i] == '"' || s[i] == '\'')
			in_quotes = !in_quotes;
		if (s[i] && s[i] != b)
		{
			cnt++;
			while (s[i] && (s[i] != b || in_quotes))
			{
				if (s[i] == '"' || s[i] == '\'')
					in_quotes = !in_quotes;
				i++;
			}
		}
	}
	return (cnt);
}

static int	_allocator(char const *s, int row, char b)
{
	int	len;
	int	i;
	int	in_quotes;

	len = 0;
	i = 0;
	in_quotes = 0;
	while (s[i] == b && !in_quotes)
		i++;
	while (row--)
	{
		while (s[i] && (s[i] != b || in_quotes))
		{
			if (s[i] == '"' || s[i] == '\'')
				in_quotes = !in_quotes;
			i++;
		}
		while (s[i] == b && !in_quotes)
			i++;
	}
	while (s[i] && (s[i] != b || in_quotes))
	{
		if (s[i] == '"' || s[i] == '\'')
			in_quotes = !in_quotes;
		else
			len++;
		i++;
	}
	return (len + 1);
}

static char	*_stricpy(char *dest, char const *src, char b, int index)
{
	int	i;
	int	j;
	int	in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	while (src[j] == b && !in_quotes)
		j++;
	while (index--)
	{
		while (src[j] && (src[j] != b || in_quotes))
		{
			if (src[j] == '"' || src[j] == '\'')
				in_quotes = !in_quotes;
			j++;
		}
		while (src[j] == b && !in_quotes)
			j++;
	}
	while (src[j] && (src[j] != b || in_quotes))
	{
		if (src[j] == '"' || src[j] == '\'')
			in_quotes = !in_quotes;
		else
			dest[i++] = src[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
static char	**_check_free(char **arr, int i)
{
	if (!arr)
		return (NULL);
	while (i >= 0)
	{
		free(arr[i]);
		arr[i] = NULL;
		i--;
	}
	free(arr);
	arr = NULL;
	return (arr);
}
char	**_ft_split(char const *s, char b)
{
	char	**arr;
	int		i;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (_words(s, b) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < _words(s, b))
	{
		arr[i] = (char *)malloc(_allocator(s, i, b));
		if (!arr[i])
			return (_check_free(arr, i));
		i++;
	}
	i = 0;
	while (i < _words(s, b))
	{
		arr[i] = _stricpy(arr[i], s, b, i);
		i++;
	}
	arr[_words(s, b)] = NULL;
	return (arr);
}


void	throw_error(int error)
{
	if (error == SYNTAX)
		printfd(2, "Invalid Syntax : Something is missing \" or ' or ( or )\n");
	if (error == OP)
		printfd(2, "Invalid Syntax : Error in operators input\n");
	if (error == CMD_NOT_FOUND)
		printfd(2, "Command not found : %s\n", g_vars.cmd_not_found);
	g_vars.exit = 127;
}

int	ft_nodejoin(void)
{
	char *(new_content), *(tmp_content);
	t_list *(to_delete), *(tmp) = g_vars.args;
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	while (tmp && tmp->next)
	{
		tmp_content = (char *)tmp->content;
		if (!is_op(tmp_content) && !is_op((char *)tmp->next->content) && \
			!is_par(tmp_content) && !is_par((char *)tmp->next->content))
		{
			new_content = ft_strjoin(tmp_content, (char *)tmp->next->content);
			if (!new_content)
				return (FALSE);
			free(tmp->content);
			tmp->content = new_content;
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			ft_lstdelone(to_delete, free);
		}
		else
			tmp = tmp->next;
	}
	if (tmp && is_op((char *)tmp->content))
		return (throw_error(OP), FALSE);
	return (TRUE);
}

void	print_array(char **arr)
{
	int (i) = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		printf("words %d : '%s'\n", i, arr[i]);
		i++;
	}
}

char	**linkedlist_to_array(t_list *tmp_arr)
{
	char	**arr;

	int (i), (words);
	if (!tmp_arr)
		return (NULL);
	words = ft_lstsize(tmp_arr);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < words && tmp_arr)
	{
		arr[i] = ft_strdup(tmp_arr->content);
		if (!arr[i++])
			return (ft_free("2", arr), NULL);
		tmp_arr = tmp_arr->next;
	}
	arr[words] = NULL;
	i = 0;
	while (arr[i])
	{
		arr[i] = removequotes(arr[i]);
		i++;
	}
	print_array(arr);
	return (arr);
}

void	split_cmds_args(void)
{
	// char	*token;
	// t_list	*tmp_arr;

	g_vars.tmp = g_vars.args;
	while (g_vars.tmp)
	{
		// tmp_arr = NULL;
		// token = strtok(g_vars.tmp->content, " ");
		// while (token)
		// {
		// 	while (token && *token == ' ')
		// 	{
		// 		free(token);
		// 		token = strtok(NULL, " ");
		// 	}
		// 	if (token && *token)
		// 		ft_lstadd_back(&tmp_arr, ft_lstnew(token));
		// 	token = ft_strtok(NULL, " ");
		// }
		// ft_lstiter(tmp_arr, printf);
		// g_vars.tmp->arr = linkedlist_to_array(tmp_arr);
		// printf("maine\n");
		// ft_lstclear(&tmp_arr, free);
		g_vars.tmp->arr = _ft_split(g_vars.tmp->content, ' ');
		print_array(g_vars.tmp->arr);
		g_vars.tmp = g_vars.tmp->next;
	}
	// ft_lstclear(&tmp_arr, free);
}

int	fill_args(void)
{
	char	*token;

	if (!g_vars.cmd || !*(g_vars.cmd) || ft_iswhitespace(g_vars.cmd))
		return (FALSE);
	token = ft_strtok(g_vars.cmd, "'\"()|&><");
	while (token)
	{
		if (!ft_iswhitespace(token))
		{
			ft_lstadd_back(&g_vars.args, ft_lstnew(token));
			g_vars.args->arr = NULL;
		}
		token = ft_strtok(NULL, "'\"()|&><");
	}
	if (!ft_check())
		return (FALSE);
	g_vars.tmp = g_vars.args;
	ft_lstiter(g_vars.tmp, printf);
	split_cmds_args();
	return (TRUE);
}

//we shoud implement the fct that parses the peripheric of the paranthesis
// () )(  &(&)  ()|  ()a : nooooo
// >> << ()
//  (ls )(cat -e M)
