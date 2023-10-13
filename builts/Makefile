# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: araji-af <araji-af@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 17:57:42 by araji-af          #+#    #+#              #
#    Updated: 2023/10/12 17:48:09 by araji-af         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = cd_cmd.c echo.c env.c export_utils.c export.c pwd.c unset_utils.c unset.c utils.c main.c exit.c \
	ft_printf.c ft_printf_utils.c ft_printf_bases.c

NAME = minishell

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

%.o : %.c builtins.h
	cc $(FLAGS) -c $< -o $@ 

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -rf $(OBJ)
	
fclean : clean
	rm -rf $(NAME)

re : fclean all