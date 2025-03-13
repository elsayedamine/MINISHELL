/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 03:26:12 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/13 03:48:39 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	_words(char const *s, char b)
{
	int (cnt), (i), (q);
	ft_init(3, &cnt, &i, &q);
	while (s[i])
	{
		while (s[i] == b && !q)
			i++;
		if (s[i] == '"' || s[i] == '\'')
			q = s[i];
		if (s[i] && s[i] != b)
		{
			cnt++;
			while (s[i] && (s[i] != b || q))
			{
				if (s[i] == q)
					q = 0;
				i++;
			}
		}
	}
	return (cnt);
}

static int	_allocator(char const *s, int row, char b)
{
	int (len), (i), (q);
	ft_init(3, &len, &i, &q);
	while (s[i] == b && !q)
		i++;
	while (row--)
	{
		while (s[i] && (s[i] != b || q))
		{
			if (s[i] == '"' || s[i] == '\'')
				q = s[i];
			i++;
		}
		while (s[i] == b && !q)
			i++;
	}
	while (s[i] && (s[i] != b || q))
	{
		if (s[i] == '"' || s[i] == '\'')
			q = 0;
		else
			len++;
		i++;
	}
	return (len + 1);
}

static char	*_stricpy(char *dest, char const *src, char b, int index)
{
	int (j), (i), (q);
	ft_init(3, &j, &i, &q);
	while (src[j] == b && !q)
		j++;
	while (index--)
	{
		while (src[j] && (src[j] != b || q))
		{
			if (src[j] == '"' || src[j] == '\'')
				q = src[j];
			j++;
		}
		while (src[j] == b && !q)
			j++;
	}
	while (src[j] && (src[j] != b || q))
	{
		if (src[j] == '"' || src[j] == '\'')
			q = 0;
		else
			dest[i++] = src[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
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
			return (ft_free("2", arr), NULL);
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
