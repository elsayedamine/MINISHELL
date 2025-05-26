/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:59:00 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/26 16:30:57 by ahakki           ###   ########.fr       */
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

int c_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (-1);
	while ((entry = readdir(dir)) != NULL)
		count++;
	closedir(dir);
	return (count);
}

char	**wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;

	matches = (char **)alloc(sizeof(char *) * (c_files() + 1), NULL, 'M');
	count = 0;
	dir = opendir(".");
	if ((!matches && dir && closedir(dir)) || !dir)
		return (throw_error(DIRECT, NULL, NULL), NULL);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			if (count < MAX_MATCHES)
				matches[count++] = alloc(0, ft_strdup(entry->d_name), 0);
			else
				break ;
		}
		entry = readdir(dir);
	}
	if (!count)
		return (NULL);
	return (closedir(dir), matches[count] = NULL, matches);
}
