/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:59:00 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/29 22:19:35 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	match_pattern(const char *pattern, const char *str)
{
	if (!pattern || !str)
		return (FALSE);
	while (*pattern)
	{
		if (*pattern == '*')
		{
			pattern++;
			if (!*pattern)
				return (TRUE);
			while (*str)
			{
				if (match_pattern(pattern, str))
					return (TRUE);
				str++;
			}
			return (FALSE);
		}
		if (*pattern != *str)
			return (FALSE);
		pattern++;
		str++;
	}
	return (*str == '\0');
}

int	c_files(void)
{
	DIR				*dir;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	while (readdir(dir))
		count++;
	closedir(dir);
	return (count);
}

char	*trim_pattern(char *pattern)
{
	int		start;
	int		end;
	char	*res;

	start = 0;
	end = 0;
	if (pattern && *pattern == '*')
		start = 1;
	if (pattern[ft_strlen(pattern) - 1] == '*')
		end = 1;
	res = (char *)alloc(0, ft_strtrim(pattern, "*"), 0);
	if (!res)
		return (NULL);
	if (start == 1)
		res = alloc(0, ft_strjoin("*", res), 0);
	if (end == 1)
		res = alloc(0, ft_strjoin(res, "*"), 0);
	return (res);
}

char	**wildcard(char *pattern)
{
	t_wc	wc;

	wc.tmp = trim_pattern(pattern);
	wc.matches = (char **)alloc(sizeof(char *) * (c_files() + 1), NULL, 'M');
	wc.count = 0;
	wc.dir = opendir(".");
	if ((!wc.matches && wc.dir && closedir(wc.dir)) || !wc.dir)
		return (throw_error(DIRECT, NULL, NULL), NULL);
	wc.entry = readdir(wc.dir);
	while (wc.entry)
	{
		if (match_pattern(wc.tmp, wc.entry->d_name))
		{
			if (wc.entry->d_name[0] != '.' || \
				(*pattern == '.' && wc.entry->d_name[0] == '.'))
				wc.matches[wc.count++] = alloc(0, \
					ft_strdup(wc.entry->d_name), 0);
		}
		wc.entry = readdir(wc.dir);
	}
	if (!wc.count)
		return (closedir(wc.dir), NULL);
	return (closedir(wc.dir), wc.matches[wc.count] = NULL, wc.matches);
}
