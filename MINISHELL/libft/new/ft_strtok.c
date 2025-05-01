/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayed <sayed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:16:51 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/23 23:01:49 by sayed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*handle_quotes(char **next_token)
{
	char	*start;
	char	quote;

	quote = *(*next_token)++;
	start = *next_token - 1;
	while (**next_token && **next_token != quote)
		(*next_token)++;
	if (**next_token == quote)
		(*next_token)++;
	return (ft_strndup(start, *next_token - start));
}

static char	*handle_op(char **next_token)
{
	char	*start;

	start = *next_token;
	if (**next_token == '>' && *(*next_token + 1) == '>')
		return ((*next_token) += 2, ft_strdup(">>"));
	if (**next_token == '<' && *(*next_token + 1) == '<')
		return ((*next_token) += 2, ft_strdup("<<"));
	if (**next_token == '&' && *(*next_token + 1) == '&')
		return ((*next_token) += 2, ft_strdup("&&"));
	if (**next_token == '|' && *(*next_token + 1) == '|')
		return ((*next_token) += 2, ft_strdup("||"));
	(*next_token)++;
	return (ft_strndup(start, 1));
}

char	*ft_strtok(char *str, char const *delim)
{
	static char	*next_token;
	char		*start;

	if (!str && !next_token)
		return (NULL);
	if (str)
		next_token = str;
	if (!next_token || !*next_token)
		return (NULL);
	if ((*next_token == '\'' || *next_token == '"'))
		return (handle_quotes(&next_token));
	if (ft_strchr("&|", *next_token))
		return (handle_op(&next_token));
	if (ft_strchr(delim, *next_token))
		return (ft_strndup(next_token++, 1));
	start = next_token;
	while (*next_token && !ft_strchr(delim, *next_token))
		next_token++;
	return (ft_strndup(start, next_token - start));
}
