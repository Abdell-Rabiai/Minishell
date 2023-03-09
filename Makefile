# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/03/09 18:56:11 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_OBJ = $(shell ls *.c | grep -v minishell_main.c) $(shell ls builtin_functions/*.c )

SRC = minishell_main.c

FLAGS = -Wall -Werror -Wextra 
#-g -fsanitize=address

CC = cc

LIBS = libft/libft.a libftprintf.a

OBJ = $(SRCS_OBJ:.c=.o)

all : libftprintf $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) minishell.h minishell_main.c
	make -C libft/
	$(CC) $(FLAGS) $(SRC) $(OBJ) $(LIBS) -lreadline -o $(NAME)

libftprintf :
	make -C ft_printf/
	@cd ft_printf && make

clean :
	make clean -C libft
	make clean -C ft_printf
	rm -rf $(OBJ)

fclean : clean
	make fclean -C libft
	rm -rf $(LIBS) $(NAME)
	rm -rf *.dSYM .vscode

re : fclean all

.PHONY : all clean fclean re