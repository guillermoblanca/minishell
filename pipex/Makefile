# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leiamart <leiamart@student.42malaga.c      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/23 13:17:26 by leiamart          #+#    #+#              #
#    Updated: 2024/11/30 15:55:02 by leiamart         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = pipex
NAME_BONUS = pipexbonus
CC = clang
CFLAGS = -g -Wall -Wextra -Werror

SOURCES = \
arg_pipex.c\
ft_child_process.c\
ft_free.c\
ft_printf.c\
ft_split.c\
ft_utils_printf.c\
pipex.c\
utils_pipex.c\
pipex_utils.c\

SOURCES_BONUS = \
./bonus/ft_child_bonus.c\
./bonus/ft_fd_bonus.c\
./bonus/ft_free_bonus.c\
./bonus/ft_here_doc_bonus.c\
./bonus/ft_pipex_bonus.c\
./bonus/utils_bonus.c\
./bonus/ft_split_bonus.c\
./bonus/get_next_line_utils_pipex_bonus.c\
./bonus/get_next_line_pipex_bonus.c\
./bonus/ft_printf_bonus.c\
./bonus/ft_printf_u_bonus.c\
./bonus/arg_pipex_bonus.c\
./bonus/ft_utils_pipex_bonus.c\

SOURCES_DIR_BONUS = ./bonus/

OBJECTS = $(SOURCES:.c=.o)

OBJECTS_BONUS = $(SOURCES_BONUS:.c=.o)

all: $(NAME)

%.o:%.c
	$(CC) -g $(FLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	   $(CC) -g $(FLAGS) $(OBJECTS) -o $(NAME)

$(NAME_BONUS) : $(OBJECTS_BONUS)
	$(CC) $(CFLAGS) $(OBJECTS_BONUS) -o $(NAME_BONUS)

bonus: $(NAME_BONUS)

clean:
	rm -f $(OBJECTS) $(OBJECTS_BONUS)


fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re

