CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
NAME = libft.a
SOURCES = \
		printfd/fd_numbers.c \
		printfd/fd_pointers.c \
		printfd/printfd.c \
		printfd/ft_printf.c \
		\
		\
		get_next_line/get_next_line.c \
		\
		\
		new/ft_iswhitespace.c \
		new/ft_strchr_index.c \
		new/ft_arrlen.c \
		new/ft_strcmp.c \
		new/ft_strndup.c \
		new/ft_strtok.c \
		new/ft_init.c \
		new/ft_free.c \
		new/ft_malloc.c \
		new/int_free.c \
		new/ft_read.c \
		new/lst_new.c \
		new/lst_addback.c \
		new/lst_addfront.c \
		new/lst_clear.c \
		new/lst_last.c \
		new/lst_size.c \
		new/ft_count_char.c \
		new/ft_insert_char.c \
		\
		\
		base/ft_isalnum.c \
		base/ft_isalpha.c \
		base/ft_isascii.c \
		base/ft_isdigit.c \
		base/ft_isprint.c \
		base/ft_tolower.c \
		base/ft_toupper.c \
		base/ft_atoi.c \
		base/ft_itoa.c \
		base/ft_split.c \
		base/ft_strchr.c \
		base/ft_strdup.c \
		base/ft_striteri.c \
		base/ft_strjoin.c \
		base/ft_strlcat.c \
		base/ft_strlcpy.c \
		base/ft_strlen.c \
		base/ft_strmapi.c \
		base/ft_strncmp.c \
		base/ft_strnstr.c \
		base/ft_strrchr.c \
		base/ft_strtrim.c \
		base/ft_substr.c \
		base/ft_bzero.c \
		base/ft_calloc.c \
		base/ft_memchr.c \
		base/ft_memcmp.c \
		base/ft_memcpy.c \
		base/ft_memmove.c \
		base/ft_memset.c \
		base/ft_putchar_fd.c \
		base/ft_putendl_fd.c \
		base/ft_putnbr_fd.c \
		base/ft_putstr_fd.c \
		base/ft_lstadd_back_bonus.c \
		base/ft_lstadd_front_bonus.c \
		base/ft_lstclear_bonus.c \
		base/ft_lstdelone_bonus.c \
		base/ft_lstiter_bonus.c \
		base/ft_lstlast_bonus.c \
		base/ft_lstmap_bonus.c \
		base/ft_lstnew_bonus.c \
		base/ft_lstsize_bonus.c \

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJECTS)