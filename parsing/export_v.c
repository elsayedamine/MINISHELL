/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_v.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 18:04:41 by ahakki            #+#    #+#             */
/*   Updated: 2025/04/07 16:34:56 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*export_v(char *s)
{
	char	*value;

	if (!s)
		return (NULL);
	value = getenv(s);
	return (value);
}

char	*expand(char *str, char *var, int i)
{
	char	*new;
	int		len;
	int		j;
	int		k;

	ft_init(2, &j, &k);
	len = ft_strlen(str) + ft_strlen(var);
	new = (char *)malloc(sizeof(char) * (len + 1));
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	while (var && var[k])
	{
		new[j] = var[k];
		j++;
		k++;
	}
	while (str[i])
	{
		new[j] = str[i];
		j++;
		i++;
	}
	new[j] = '\0';
	return (free(str), new);
}

int	main(int ac, char **av)
{
	char	*str;
	char	*var;
	char	*temp;
	int		i;

	str = ft_strdup(av[1]);
	var = export_v(ft_strdup(av[2]));
	i = ft_strchr_index(str, '$');
	temp = expand(str, var, i);
	if (i != -1)
	{
		printf("%s\n", temp);
		free(temp);
	}
}
