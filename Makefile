# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/03/04 14:21:10 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_OBJ = $(shell ls | grep .c | grep -v main)

SRC = main.c

FLAGS = -Wall -Werror -Wextra

CC = cc

LIB = libft/libft.a

OBJ = $(SRCS_OBJ:.c=.o)

all : $(NAME)

%.o: %.c minishell.h
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) minishell.h main.c
	make -C libft/
	$(CC) $(FLAGS) $(SRC) $(OBJ) $(LIB) -lreadline -o $(NAME)
	@rm -rf $(LIBS)

clean :
	make clean -C libft
	rm -rf $(OBJ)
fclean : clean
	make fclean -C libft
	rm -rf $(LIBS) $(NAME)

re : fclean all

.PHONY : all clean fclean re