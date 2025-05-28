/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelsayed <aelsayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:18:16 by aelsayed          #+#    #+#             */
/*   Updated: 2025/05/28 22:51:55 by aelsayed         ###   ########.fr       */
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
# define IN 0
# define OUT 1

/* **************************************** */
/*                 ENUMS                    */
/* **************************************** */

typedef enum error
{
	SYNTAX = 512,
	DIRECT,
	REDIR,
	CMD_NOT_FOUND,
	VALID_BUILT,
	INVALID_BUILT,
	NOT_BUILT,
	EOOF,
}			t_error;

typedef enum type
{
	OR,
	AND,
	SUBSHELL,
	PIPE,
	CMD,
	READ,
	HEREDOC,
	TRUNC,
	APPEND
}			t_type;

/* **************************************** */
/*             STRUCTURES                   */
/* **************************************** */

typedef struct s_pipeline
{
	int					type;
	char				*cmd;
	t_list				*sub;
}						t_pipeline;

typedef struct s_stream
{
	int	read;
	int	write;
}		t_stream;

typedef struct s_pipe
{
	t_list		*pipeline;
	int			size;
	int			pos;
	int			exit_status;
	pid_t		last_pid;
	t_stream	*stream_line;
}				t_pipe;

typedef struct s_redir
{
	t_type	mode;
	int		fd;
	int		flag;
	int		q;
	char	*target;
	char	*delim;
}			t_redir;

typedef struct s_wild
{
	int		*b;
	char	**arr;
	char	*pattern;
	int		diff;
	t_list	*node;
}			t_wd;

typedef struct s_sig
{
	int		flag;
	int		exit_status;
}			t_sig;

typedef struct s_check
{
	int		dquot;
	int		squot;
	int		lpar;
	int		fpar;
	int		par;
	int		special;
}			t_check;

typedef struct s_err
{
	int		errn;
	char	*str;
}			t_err;

// Main shell structure
typedef struct s_shell
{
	int			exit;
	int			bash_line_counter;
	int			*fds;
	int			exec;
	char		**envp;
	char		*cmd;
	char		*cmd_not_found;
	char		*pwd;
	t_list		*heredoc;
	t_list		*env;
	t_list		*args;
	t_list		*tmp;
	t_list		*redir;
	t_list		*ast;
	t_check		check;
	t_err		err;
}				t_shell;

typedef int (t_fct)(int ac, char **av, t_shell *vars);

extern t_sig	*g_var;

/* **************************************** */
/*           FUNCTION PROTOTYPES            */
/* **************************************** */

/*---------------------------- PARSING ----------------------------*/

/* Building */
t_list		*ast_builder(t_list **cursor);
int			fill_args(t_shell *vars);
t_list		*create_node(void *content);
char		*tokenizer(char *str, char const *delim);
void		ft_nullenv(t_shell *vars);
void		ft_shlvl(t_shell *vars);
t_type		define_type(char *content);
t_redir		*create_redir_node(t_shell *vars, t_type mode, char *target);
t_list		*create_redir_list(t_shell *vars, t_list **s);
t_list		*tokenize_command(char *cmd);

/* Validation */
int			all_checks(t_shell *vars);
int			isvalid_par(t_shell *vars);
int			isvalid_red(t_shell *vars);
int			isvalid_op(t_shell *vars);
int			is_op(char *str);
int			is_par(char *str);
int			isvalid_quotes(t_shell *vars);
int			is_there_red(char *str);
int			is_red(char *str, char r);
int			nodejoin(t_shell *vars);
char		**_ft_split(char const *s, char b);

/* Processing */
int			ft_nodejoin(t_shell *vars);
char		*removequotes(char *str, t_list *s);
char		*old_removequotes(char *str);
t_list		*remove_quotes_from_list(t_list *lst);
char		**_ft_split(char const *s, char b);
void		pop_spaces(t_shell *vars);
void		throw_error(int error, char *file, int *status);
int			process_heredocs(t_shell *vars);
t_redir		*get_heredoc_node(t_shell *vars);

/* Expansion */
char		**split_list(t_list *lst, char sep);
void		expand(t_shell *vars, char **str, char ***arr);
char		**wildcard(char *pattern);
int			append(t_list **s, char c, int type);
char		*expand_wildcard(char **str, t_list **s);
t_list		*ft_str_to_lst(char *str, int flag);
int			get_var_len(char *str);
int			extract_var_value(t_shell *vars, t_list **s, char *str, int q);
t_list		*breakdown(t_shell *vars, char *str);
int			expand_target(t_shell *vars, char **str);
t_list		*skip_nodes(t_list **head, t_list *node);

/*---------------------------- BUILTINS ----------------------------*/

int			cd(int ac, char **av, t_shell *vars);
int			echo(int ac, char **av, t_shell *vars);
int			env(int ac, char **av, t_shell *vars);
int			ft_exit(int ac, char **av, t_shell *vars);
int			pwd(int ac, char **av, t_shell *vars);
int			unset(int ac, char **av, t_shell *vars);
int			export(int ac, char **av, t_shell *vars);
char		*get_env(char *k, t_shell *vars);
char		*ft_strjoin_f(char *s1, char *s2, int free_s);
void		ft_printexport(t_shell	*vars);
void		append_value(char *v, char *av, t_shell *vars);
int			check_builts(char **arr, t_shell *vars, int i);
int			is_built(char **arr, t_shell *vars);

/*---------------------------- EXECUTION ----------------------------*/

int			pipex(t_shell *vars, t_list **node);
int			execution(t_shell *vars, t_list **ast, t_list **parent);
char		*get_path(char *cmd, t_shell *vars);
int			exit_execve(char *cmd, t_shell *vars, t_list **ast);
void		skip(t_list **node, int op);
int			traverse_sub(t_shell *vars, t_list **node);
int			execute_cmd(t_shell *vars, t_list **ast);
int			check_builts(char **arr, t_shell *vars, int i);
int			checks(t_shell *vars, t_list **ast, char **cmd);
int			process_cmd(t_shell *vars, t_list **ast, int flag);

/*---------------------------- REIRECTIONS ----------------------------*/

int			apply_redirections(t_shell *vars);
void		extract_redirections(t_shell *vars, char **original);
int			*apply_redirect_shell(t_shell *vars);
void		perform_dups(int save_in, int save_out);
int			open_file(t_redir *r, char **filename);
void		return_original_std(t_shell *vars);	
int			*redirect_sub(t_shell *vars, t_list **ast, t_list *node);
int			open_files(t_shell *vars);

/*---------------------------- PIPELINE ----------------------------*/

int			execute_cmd_pipe(t_shell *vars, t_pipe pipe, int i);
int			pipex(t_shell *vars, t_list **ast);
pid_t		execute_pipe(t_shell *vars, t_pipe *pipe, int index);
void		stream2io(t_stream *stream);
void		shut_stream(t_stream *curr_stream);
void		connect_pipe(t_stream *curr_stream);
t_stream	*streams_init(int pipeline_len);
int			exit_execve(char *cmd, t_shell *vars, t_list **ast);
int			wait_child_processes(t_pipe *pipe);
t_pipe		create_pipeline(t_list **ast);
int			check_built(char **arr, t_shell *vars);

/*---------------------------- ALLOCS ----------------------------*/

void		*alloc(size_t n, void *content, char c);
char		**ft_arrdup(char **arr);
t_list		*ft_arr2list(char **arr);
char		**ft_list2arr(t_list *lst);
void		clear(int sig);
void		foo(int sig);

#endif
