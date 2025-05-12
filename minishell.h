/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/12 02:42:34 by aelsayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* **************************************** */
/*                INCLUDES                  */
/* **************************************** */

# include "libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/dir.h>
# include <readline/readline.h>
# include <readline/history.h>

/* **************************************** */
/*              DEFINITIONS                 */
/* **************************************** */

# define M "Minishell"
# define MAX_MATCHES 1024

/* **************************************** */
/*                 ENUMS                    */
/* **************************************** */

typedef enum error
{
	IN = 512,
	OUT,
	SYNTAX,
	CHARS,
	OP,
	DUP,
	EXEC,
	PIP,
	DIRECT,
	CMD_NOT_FOUND
}			t_error;

typedef enum type
{
	OR,
	AND,
	SUBSHELL,
	PIPE,
	CMD,
	READ,
	WRITE,
	APPEND,
	HEREDOC 
}			t_type;

/* **************************************** */
/*             STRUCTURES                   */
/* **************************************** */

typedef struct s_pipe
{
	int		*fdo;
	int		*fdi;
	pid_t	pid1;
	pid_t	pid2;
	char	*path1;
	char	*path2;   
	char	**args;
	int		pipefd[2];
}			t_pip;

typedef struct s_check
{
	int		dquot;
	int		squot; 
	int		lpar;
	int		fpar; 
	int		par;
	int		special;
}			t_check;

// Main shell structure
typedef struct s_shell
{
	int			exit;
	char		**envp;
	char		*cmd;
	char		*cmd_not_found;
	char		*pwd;
	t_list		*env;
	t_list		*args;
	t_list		*tmp;
	t_check		check;
	t_list		*ast;
}				t_shell;

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

/*-------------------------------------- PARSING --------------------------------------*/

/* Building */
t_list	*ast_builder(t_list **cursor);
int		fill_args(t_shell *vars);
t_list	*create_node(void *content);

/* Validation */
int		ft_check(t_shell *vars);
int		isvalid_par(t_shell *vars);
int		isvalid_op(t_shell *vars);
int		is_op(char *str);
int		is_par(char *str);
int		isvalid_quotes(t_shell *vars);

/* Processing */
int		ft_nodejoin(t_shell *vars);
char	*removequotes(char *str, t_list *s);
// char	**removequotes_arr(char **arr);
t_list	*remove_quotes_from_list(t_list *lst);
char	**_ft_split(char const *s, char b);
void	pop_spaces(t_shell *vars);

void	throw_error(int error, char *file, int *status);

/* Expansion */
char	**split_list(t_list *lst, char sep);
void	expand(t_shell *vars, char **str, char ***arr);
char	**wildcard(char *pattern);
int		add_char(t_list **s, char c);
char	*expand_wildcard(t_shell *vars, char **str, t_list **s);
t_list	*ft_str_to_lst(char *str, int flag);

/*-------------------------------------- BUILTINS --------------------------------------*/

int		cd(int ac, char **av, t_shell *vars);
int		echo(int ac, char **av, t_shell *vars);
int		env(int ac, char **av, t_shell *vars);
int		ft_exit(int ac, char **av, t_shell *vars);
int		export(int ac, char **av, t_shell *vars);
int		pwd(int ac, char **av, t_shell *vars);
int		unset(int ac, char **av, t_shell *vars);
char	*get_env(char *k, t_shell *vars);

/*-------------------------------------- execution --------------------------------------*/

int		pipex(t_shell *vars, t_list **node);
int		execution(t_shell *vars, t_list **ast);
char	*get_path(char *cmd, t_shell *vars);
void	exit_execve(char *cmd, t_shell *vars, t_list **ast);
void	skip(t_list **node, int op);
int		traverse_sub(t_shell *vars, t_list **node);
int		execute_cmd(t_shell *vars, t_list **ast);
int		check_builts(char **arr, t_shell *vars);
#endif
