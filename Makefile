# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/03/11 17:28:34 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

bold := $(shell tput bold)
sgr0 := $(shell tput sgr0)

SRCS_OBJ = $(shell ls *.c | grep -v minishell_main.c) $(shell ls builtin_functions/*.c )

SRC = minishell_main.c

FLAGS = -Wall -Werror -Wextra #-g -fsanitize=address

CC = cc

LIBS = libft/libft.a libftprintf.a

echo1 = @echo "\033[92mCompiled MINISHELL files successfully !!! :) \033[0m"
echo2 = @echo "\033[36mMINISHELL created successfully !!! :) \033[m"
echo3 = @echo "\033[31mMINISHELL Objects removed successfully !!! :) \033[m"
echo4 = @echo "\033[31mMINISHELL removed successfully !!! :) \033[m"

OBJ = $(SRCS_OBJ:.c=.o)

all : libftprintf $(NAME)

%.o: %.c minishell.h
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ) minishell.h minishell_main.c
	$(echo1)
	@$(CC) $(FLAGS) $(SRC) $(OBJ) $(LIBS) -lreadline -o $(NAME)
	$(echo2)

libftprintf :
	@make -C libft/
	@make -C ft_printf/

clean :
	@make clean -C libft
	@make clean -C ft_printf
	@rm -rf $(OBJ)
	$(echo3)

fclean : clean
	@rm -rf $(LIBS) $(NAME)
	@rm -rf *.dSYM .vscode
	$(echo4)

re : fclean all

.PHONY : all clean fclean re