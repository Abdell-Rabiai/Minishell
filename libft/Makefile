# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabiai <arabiai@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/25 18:47:21 by ahmaymou          #+#    #+#              #
#    Updated: 2023/03/11 17:28:12 by arabiai          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_isalpha.c ft_memcmp.c ft_strdup.c ft_strnstr.c \
        ft_atoi.c ft_isascii.c ft_memcpy.c ft_strlcat.c    ft_strrchr.c \
        ft_bzero.c ft_isdigit.c ft_memmove.c ft_strlcpy.c ft_tolower.c \
        ft_calloc.c  ft_isprint.c ft_memset.c ft_strlen.c ft_toupper.c \
        ft_isalnum.c ft_memchr.c ft_strchr.c ft_strncmp.c ft_strjoin.c ft_substr.c \
		ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_split.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_strcmp.c

BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECT = $(SRC:.c=.o)

BONUS_OBJECT = $(BONUS_SRC:.c=.o)

CC = cc

echo1 = @echo "\033[92mCompiled LIBFT files successfully !!! :) \033[0m"
echo2 = @echo "\033[92mCompiled bonus LIBFT files successfully !!! :) \033[0m"
echo3 = @echo "\033[36mLIBFT created successfully !!! :) \033[m"
echo4 = @echo "\033[36mbonus added to the LIBFT successfully !!! :) \033[m"

echo5 = @echo "\033[31mLIBFT Objects removed successfully !!! :) \033[m"
echo6 = @echo "\033[31mLIBFT removed successfully !!! :) \033[m"

FLAGS = -Wall -Wextra -Werror

all : $(NAME) bonus

%.o: %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJECT) libft.h
#@$(echo1)
	@ar rc $(NAME) $(OBJECT)
#@$(echo3)

bonus : $(NAME) $(BONUS_OBJECT)
#@$(echo2)
	@ar rc $(NAME) $(OBJECT) $(BONUS_OBJECT)
#@$(echo4)

clean :
	@rm -rf $(OBJECT) $(BONUS_OBJECT)
#@$(echo5)

fclean : clean
	@rm -rf $(NAME)
#@$(echo6)

re : fclean all

re_b:fclean bonus
	

#a : all bonus
	
#.PHONY : clean fclean all re bonus