
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
