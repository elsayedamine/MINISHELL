/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:59:00 by ahakki            #+#    #+#             */
/*   Updated: 2025/05/09 16:31:35 by aelsayed         ###   ########.fr       */
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

void	wildcard(const char *pattern, t_list **x)
{
	DIR				*dir;
	struct dirent	*entry;
	char			**matches;
	int				count;

	count = 0;
	matches = (char **)malloc(sizeof(char *) * (MAX_MATCHES + 1));
	dir = opendir(".");
	if (!matches || !dir)
		return (ft_free("1", matches), throw_error(DIRECT, NULL, NULL));
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && match_pattern(pattern, entry->d_name))
		{
			if (count < MAX_MATCHES)
				matches[count++] = ft_strdup(entry->d_name);
			else
				break ;
		}
		entry = readdir(dir);
	}
	matches[count] = NULL;
	*x = ft_arr2list(matches);
	return (closedir(dir), (void)ft_free("2", matches));
}

// int	main(int ac, char **av)
// {
// 	char	**matches;
// 	int		i;

// 	i = 0;
// 	if (ac == 1)
// 		return (0);
// 	matches = wildcard_match(av[1]);
// 	if (matches)
// 	{
// 		while (matches[i] != NULL)
// 			printf("Match: %s\n", matches[i++]);
// 		ft_free("2", matches);
// 	}
// 	else
// 		printfd(2, "No matches found or an error occurred.\n");
// 	return (0);
// }
