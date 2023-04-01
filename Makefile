# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/09 14:24:42 by ahmaymou          #+#    #+#              #
#    Updated: 2023/04/01 20:52:14 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

Color_Off=\033[0m
LIGHTRED=\033[1;31m
LightBlue=\033[1;34m
LightPurple=\033[1;35m
Cyan=\033[0;36m
GREEN = \033[92m

BANNER=\
'   ▄▄▄▄███▄▄▄▄     ▄█  ███▄▄▄▄     ▄█     ▄████████    ▄█    █▄       ▄████████   ▄█        ▄█       '\
' ▄██▀▀▀███▀▀▀██▄  ███  ███▀▀▀██▄  ███    ███    ███   ███    ███     ███    ███  ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███▌   ███    █▀    ███    ███     ███    █▀   ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███▌   ███         ▄███▄▄▄▄███▄▄  ▄███▄▄▄      ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███▌ ▀███████████ ▀▀███▀▀▀▀███▀  ▀▀███▀▀▀      ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███           ███   ███    ███     ███    █▄   ███       ███       '\
' ███   ███   ███  ███  ███   ███  ███     ▄█    ███   ███    ███     ███    ███  ███▌    ▄ ███▌    ▄ '\
'  ▀█   ███   █▀   █▀    ▀█   █▀   █▀    ▄████████▀    ███    █▀      ██████████  █████▄▄██ █████▄▄██ '\
'                                                                            ▀         ▀         	  '
                                                                                                     
																									 
parser = $(addprefix src/a_parser/,expansions.c files_opener.c files_opener2.c final_list.c split_cmds.c)

lexer = $(addprefix src/a_lexer/,fill_check_1st_list.c get_words.c syntax_checker.c syntax_checker2.c syntax_checker3.c)

execution = $(addprefix src/execution/,child_processes_helpers.c execute_helpers.c initialize_data.c\
		execute_helpers1.c execute.c heredoc_helpers.c heredoc.c multiple_cmds.c multiple_cmds_helpers.c handle_signals.c)

ebuiltin_functions = $(addprefix src/ebuiltin_functions/,echo.c env.c cd.c export.c export_helpers.c export_helpers1.c\
	cd_helpers1.c unset.c basic_builtins.c env_helpers.c)

SRCS_OBJ = $(execution) $(ebuiltin_functions) $(parser) $(lexer)

SRC = src/execution/mainex.c

FLAGS = -Wall -Werror -Wextra

HEADER = src/minishell.h

CC = cc

LIBS = src/libft/libft.a src/ft_printf/libftprintf.a

OS = $(shell uname)

ifeq ($(OS),Darwin)
	READLINE_INC = -I $(shell brew --prefix readline)/include
	READLINE_LIB = -L $(shell brew --prefix readline)/lib
endif

OBJ = $(SRCS_OBJ:.c=.o)

all : banner2 libftprintf $(NAME)

banner2:
	@clear
	@echo "\n"
	@echo "$(LightPurple)"
	@for s in $(BANNER) ; do \
		printf "%s\n" "$$s" ; \
		sleep 0.03 ; \
	done ; \
	echo "$(LIGHTRED)                     Copyright : Black-Hole1004, Abdell-rabiai :) \n$(Color_Off)"

%.o: %.c $(HEADER)
	@printf "$(GREEN) Generating minishell objects... %-33.33s\r" $@
	@$(CC) $(FLAGS) $(READLINE_INC) -c $< -o $@

$(NAME) : $(OBJ) $(SRC) $(HEADER)
	@$(CC) $(FLAGS) $(SRC) $(OBJ) $(LIBS) -lreadline $(READLINE_LIB) -o $(NAME)
	@echo "\n\n\t$(Cyan) Enjoooy :)\n $(Color_Off)"

libftprintf :
	@make bonus -C src/libft/
	@make -C src/ft_printf/

clean :
	@make clean -C src/libft
	@make clean -C src/ft_printf
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -C src/libft
	@make fclean -C src/ft_printf
	@rm -rf $(LIBS) $(NAME)
	@rm -rf *.dSYM .vscode

re : fclean all

.PHONY : all clean fclean re
