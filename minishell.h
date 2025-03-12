/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/03/11 23:37:41 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "pipex/pipex.h"

typedef enum error
{
	SYNTAX,
	CHARS,
	OP,
	CMD_NOT_FOUND
}			t_error;

typedef struct s_check
{
	int		dquot;
	int		squot;
	int		lpar;
	int		fpar;
	int		par;
	int		special;
}				t_check;

typedef struct s_shell
{
	char		**envp;
	char		*cmd;
	char		*cmd_not_found;
	t_list		*args;
	t_list		*tmp;
	t_check		check;
	int			exit;
}				t_shell;

// Parsing Functions
int		fill_args(void);
int		ft_check(void);
int		isvalid_par(void);
int		ft_nodejoin(void);
int		isvalid_op(void);
int		is_op(char *str);
int		is_par(char *str);
int		isvalid_quotes(void);
void	throw_error(int error);
char	*removequotes(char *str);
void	pop_spaces(t_list *lst);

// execution Functions
void	execution(void);

#endif