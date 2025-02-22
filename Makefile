NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB_DIR = ./libft
lib = $(LIB_DIR)/libft.a

sources = \
		main.c \
		fill_args.c

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
