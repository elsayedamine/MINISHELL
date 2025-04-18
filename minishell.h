/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/04/18 12:07:01 by aelsayed         ###   ########.fr       */
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

# define M "Minishell"

typedef enum error
{
	SYNTAX,
	CHARS,
	OP,
	CMD_NOT_FOUND
}			t_error;

// typedef enum type
// {
	// NONE,
	// SUBSHELL,
	// OR,
	// AND,
	// PIPE,
	// READ,
	// WRITE,
	// APPEND,
	// HEREDOC,
	// CMD
// }			t_type;

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
char	**_ft_split(char const *s, char b);

// Built-ins Functions
int	cd(int ac, char **av, t_shell *vars);
int	echo(int ac, char **av, t_shell *vars);
int	env(int ac, char **av, t_shell *vars);
int	ft_exit(int ac, char **av, t_shell *vars);
int	export(int ac, char **av, t_shell *vars);
int	pwd(int ac, char **av, t_shell *vars);
int	unset(int ac, char **av, t_shell *vars);

// execution Functions
void	execution(t_shell *vars);
int		path_index(char **envp, char *s);
#endif