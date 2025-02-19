/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/02/19 18:28:30 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "signal.h"
# include <readline/readline.h>
# include <readline/history.h>

enum Error
{
	SYNTAX,
	CHARS,
	CMD_NOT_FOUND
};

typedef struct s_check
{
	char		dquot;
	char		squot;
	char		rpar;
	char		lpar;
	char		par;
	char		special;
	char		fpar;
}				t_check;

typedef struct s_shell
{
	char		**envp;
	char		*cmd;
	t_list		*args;
	t_list		*tmp;
	t_check		check;
	int			exit;
}				t_shell;

// Parsing Functions
void	fill_args(char *str);

#endif