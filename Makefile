NAME := minishell
CC := cc
CFLAGS := -g -Wall -Wextra -Werror
LIB_DIR := ./libft
lib = $(LIB_DIR)/libft.a

sources = \
		main.c \
		parsing/fill_args.c \
		parsing/ft_isvalid.c \
		parsing/removequotes.c \
		parsing/ft_check.c \
		parsing/expansion.c \
		parsing/wildcard.c \
		parsing/expand_wildcard.c \
		parsing/split_list.c \
		parsing/tokenizer.c \
		parsing/shlvl.c \
		parsing/ft_red_check.c \
		parsing/process_heredocs.c \
		parsing/alloc.c \
		parsing/arr_utils.c \
		\
		\
		execution/execution.c \
		execution/get_path.c \
		execution/pipeline.c \
		execution/ast_traversal.c \
		execution/redirections.c \
		execution/apply_redirections.c \
		execution/execute_builtins.c \
		\
		\
		built-ins/cd.c \
		built-ins/echo.c \
		built-ins/env.c \
		built-ins/exit.c \
		built-ins/export.c \
		built-ins/export_utils.c \
		built-ins/pwd.c \
		built-ins/unset.c \
		built-ins/get_env.c \

object = $(sources:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(lib):
	@make all -C $(LIB_DIR) > /dev/null 2>&1
	@echo "\033[32m	Libft Compiled Successfully! ✅\033[0m"

$(NAME): $(object) $(lib)
	@$(CC) $(CFLAGS) $(object) $(lib) -lreadline -o $(NAME)
	@echo "\033[32m	Minishell Compiled Successfully! ✅\033[0m"

clean:
	@rm -rf $(object)
	@make clean -C $(LIB_DIR) > /dev/null 2>&1
	@echo "\033[33m	Object Files Removed! 🗑️\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_DIR) > /dev/null 2>&1
	@echo "\033[31m	Executable removed! ❌\033[0m"

re: fclean all

flush: re clean
	@make clean -C $(LIB_DIR) > /dev/null 2>&1
	@rm -rf $(object)

f: $(object)
	@$(CC) $(CFLAGS) $(object) $(lib) -lreadline -o $(NAME)
	@rm -rf $(object)
	@echo "\033[32m	Ready To Execute! ✅\033[0m"

.SECONDARY: $(object)
.PHONY: clean fclean re all
