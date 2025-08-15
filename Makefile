NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SOURCES = \
	command.c \
	lexer.c \
	main.c \
	ft_printf.c \
	ft_utils_printf.c \
	ft_split.c \
	exit.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME) -lreadline 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
