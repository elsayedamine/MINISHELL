/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakki <ahakki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/09 13:07:52 by ahakki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
// # include "pipex/pipex.h"

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
	t_list		*_args;
	t_list		*tmp;
	t_check		check;
	int			exit;
}				t_shell;

// Parsing Functions
int		fill_args(t_shell *vars);
int		ft_check(t_shell *vars);
int		isvalid_par(t_shell *vars);
int		ft_nodejoin(t_shell *vars);
int		isvalid_op(t_shell *vars);
int		is_op(char *str);
int		is_par(char *str);
int		isvalid_quotes(t_shell *vars);
void	throw_error(int error);
char	*removequotes(char *str);
// void	pop_spaces(t_list **lst);
char	**_ft_split(char const *s, char b);

// execution Functions
void	execution(t_shell *vars);
int		path_index(char **envp, char *s);
void	print_array(char **arr);
#endif