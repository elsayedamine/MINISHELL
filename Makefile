NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror
LIB_DIR := ./libft
lib = $(LIB_DIR)/libft.a

sources = \
		main.c \
		parsing/ast_builder.c \
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
		parsing/expand_heredoc.c \
		parsing/alloc.c \
		parsing/arr_utils.c \
		\
		\
		execution/execution.c \
		execution/get_path.c \
		execution/pipeline.c \
		execution/pipeline_utils.c \
		execution/ast_traversal.c \
		execution/redirections.c \
		execution/apply_redirections.c \
		execution/shell_redirections.c \
		execution/execute_builtins.c \
		execution/stream.c \
		execution/builts.c \
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

lib_src = \
		libft/2.printfd/fd_numbers.c \
		libft/2.printfd/fd_pointers.c \
		libft/2.printfd/printfd.c \
		libft/2.printfd/ft_printf.c \
		libft/3.get_next_line/get_next_line.c \
		libft/new/ft_iswhitespace.c \
		libft/new/ft_strchr_index.c \
		libft/new/ft_arrlen.c \
		libft/new/ft_strcmp.c \
		libft/new/ft_strndup.c \
		libft/new/ft_init.c \
		libft/new/ft_free.c \
		libft/new/ft_malloc.c \
		libft/new/int_free.c \
		libft/new/ft_read.c \
		libft/new/lst_new.c \
		libft/new/lst_addback.c \
		libft/new/lst_addfront.c \
		libft/new/lst_clear.c \
		libft/new/lst_last.c \
		libft/new/lst_size.c \
		libft/new/ft_count_char.c \
		libft/new/ft_insert_char.c \
		libft/new/ft_strinsert.c \
		libft/new/ft_strstr.c \
		libft/new/ft_stristr.c \
		libft/new/ft_putarr.c \
		libft/new/ft_lstndup.c \
		libft/new/ft_lstdup.c \
		libft/new/ft_lstgetnode.c \
		libft/new/ft_str2lst.c \
		libft/new/ft_lst2str.c \
		libft/new/ft_lstpop.c \
		libft/new/ft_lstinsert.c \
		libft/new/ft_arr2str.c \
		libft/new/ft_strextract.c \
		libft/new/ft_isspace.c \
		libft/new/ft_strpbrk.c \
		libft/1.base/ft_isalnum.c \
		libft/1.base/ft_isalpha.c \
		libft/1.base/ft_isascii.c \
		libft/1.base/ft_isdigit.c \
		libft/1.base/ft_isprint.c \
		libft/1.base/ft_tolower.c \
		libft/1.base/ft_toupper.c \
		libft/1.base/ft_atoi.c \
		libft/1.base/ft_itoa.c \
		libft/1.base/ft_split.c \
		libft/1.base/ft_strchr.c \
		libft/1.base/ft_strdup.c \
		libft/1.base/ft_striteri.c \
		libft/1.base/ft_strjoin.c \
		libft/1.base/ft_strlcat.c \
		libft/1.base/ft_strlcpy.c \
		libft/1.base/ft_strlen.c \
		libft/1.base/ft_strmapi.c \
		libft/1.base/ft_strncmp.c \
		libft/1.base/ft_strnstr.c \
		libft/1.base/ft_strrchr.c \
		libft/1.base/ft_strtrim.c \
		libft/1.base/ft_substr.c \
		libft/1.base/ft_bzero.c \
		libft/1.base/ft_calloc.c \
		libft/1.base/ft_memchr.c \
		libft/1.base/ft_memcmp.c \
		libft/1.base/ft_memcpy.c \
		libft/1.base/ft_memmove.c \
		libft/1.base/ft_memset.c \
		libft/1.base/ft_putchar_fd.c \
		libft/1.base/ft_putendl_fd.c \
		libft/1.base/ft_putnbr_fd.c \
		libft/1.base/ft_putstr_fd.c \
		libft/1.base/ft_lstadd_back_bonus.c \
		libft/1.base/ft_lstadd_front_bonus.c \
		libft/1.base/ft_lstclear_bonus.c \
		libft/1.base/ft_lstdelone_bonus.c \
		libft/1.base/ft_lstiter_bonus.c \
		libft/1.base/ft_lstlast_bonus.c \
		libft/1.base/ft_lstmap_bonus.c \
		libft/1.base/ft_lstnew_bonus.c \
		libft/1.base/ft_lstsize_bonus.c

object = $(sources:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(lib): $(lib_src)
	make all -C $(LIB_DIR)

$(NAME): $(object) $(lib)
	$(CC) $(CFLAGS) $(object) $(lib) -lreadline -o $(NAME)

clean:
	rm -rf $(object)
	make clean -C $(LIB_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

flush: re clean
	make clean -C $(LIB_DIR)
	rm -rf $(object)

.SECONDARY: $(object)
.PHONY: clean fclean re all
