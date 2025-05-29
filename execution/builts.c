/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builts.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:40:26 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/29 22:40:44 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built(char **arr, t_shell *vars)
{
	(void)vars;
	if (!arr)
		return (0);
	return (!ft_strcmp("pwd", *arr)
		|| !ft_strcmp("cd", *arr)
		|| !ft_strcmp("echo", *arr)
		|| !ft_strcmp("env", *arr)
		|| !ft_strcmp("exit", *arr)
		|| !ft_strcmp("export", *arr)
		|| !ft_strcmp("unset", *arr));
	return (0);
}

int	check_built(char **arr, t_shell *vars)
{
	if (!arr)
		return (NOT_BUILT);
	if (!ft_strcmp("pwd", *arr))
		return (pwd(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("cd", *arr))
		return (cd(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("echo", *arr))
		return (echo(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("env", *arr))
		return (env(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("exit", *arr))
		return (ft_exit(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("export", *arr))
		return (export(ft_arrlen(arr), arr, vars));
	if (!ft_strcmp("unset", *arr))
		return (unset(ft_arrlen(arr), arr, vars));
	return (NOT_BUILT);
}
