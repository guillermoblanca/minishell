
NAME = Minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SOURCES = \
command.c\
compile.c\
lexer.c\
main.c\
ft_printf.c\
ft_utils_printf.c\
ft_split.c\
delete_env_unset.c\
env.c\
env_error.c\
env_export.c\
env_print.c\
ft_cd.c\
ft_errror_cd.c\
ft_exit.c\


OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CC) -g $(FLAGS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
