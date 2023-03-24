# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahmaymou <ahmaymou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 14:20:54 by arabiai           #+#    #+#              #
#    Updated: 2023/03/24 00:44:24 by ahmaymou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

bold := $(shell tput bold)
sgr0 := $(shell tput sgr0)

SOURCES = ft_printf.c ft_printf_utils.c\

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

echo1 = @echo "\033[92mCompiled PRINTF files successfully !!! :) \033[0m"
echo2 = @echo "\033[36mFT_PRINTF.A created successfully !!! :) \033[m"
echo3 = @echo "\033[31mPRINTF Objects removed successfully !!! :) \033[m"
echo4 = @echo "\033[31mFT_PRINTF.A removed successfully !!! :) \033[m

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS) ft_printf.h
#@$(echo1)
	@ar rc $(NAME) $?
#@$(echo2)

%.o: %.c ft_printf.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(RM) $(OBJECTS)
#@$(echo3)

fclean : clean
	@$(RM) $(NAME)
#@$(echo4)

re : fclean all

.PHONY : clean fclean all re
