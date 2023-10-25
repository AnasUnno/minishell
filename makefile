NAME		=	minishell

RLP=$(shell brew --prefix readline)

LDFLAGS= -L$(RLP)/lib

CIFLAGS= -I$(RLP)/include

header	=	minishell.h

CC			=	gcc

CFLAGS		=	$(CIFLAGS) -Wall -Wextra -Werror -lreadline -fsanitize=address -g

RM			=	rm -rf

SRCS		=	lib/ft_strlen.c \
				lib/ft_strchar.c \
				lib/ft_strchr.c\
				lib/ft_strncpy.c\
				lib/ft_strdup.c\
				lib/ft_strlcpy.c\
				lib/ft_strcmp.c\
				lib/ft_strtrim.c\
				lib/ft_calloc.c\
				lib/ft_putstr_fd.c\
				lib/ft_strncmp.c\
				lib/ft_split.c\
				lib/ft_strjoin.c\
				lib/ft_itoa.c\
				main.c\
				PARSER/token_utils.c\
				PARSER/token_utils2.c\
				PARSER/free_all.c\
				PARSER/check_redirections.c\
				PARSER/isValide.c\
				PARSER/error_print.c\
				AST/build_tree.c\
				EXECUTION/execution.c\
				EXECUTION/get_cmd.c\
				EXECUTION/ft_pipe.c\
				EXECUTION/left_double_r.c\
				EXECUTION/right_double_r.c\
				EXECUTION/left_r.c\
				EXECUTION/right_r.c\
				EXPANDING/create_new_str.c\
				EXPANDING/expanding.c\
				EXPANDING/get_var_value.c\
				EXPANDING/remove_quotes.c\
				EXPANDING/size_exp.c\
				BUILTINS/cd_cmd.c\
				BUILTINS/echo.c\
				BUILTINS/env.c\
				BUILTINS/exit.c\
				BUILTINS/export_utils.c\
				BUILTINS/export.c\
				BUILTINS/ft_printf_bases.c\
				BUILTINS/ft_printf_utils.c\
				BUILTINS/ft_printf.c\
				BUILTINS/pwd.c\
				BUILTINS/unset_utils.c\
				BUILTINS/unset.c\
				BUILTINS/utils.c\
				BUILTINS/utils2.c\

OBJS		= $(SRCS:.c=.o)

$(NAME)		: $(OBJS) $(header)
			$(CC) $(CFLAGS) $(OBJS)  $(LDFLAGS) -o $(NAME)

%o:%c $(header)
	$(CC) $(CIFLAGS) -c $< -o $@

all			:	$(NAME)

cm			:	all clean
	
clean		:
			$(RM) $(OBJS)

mc			: all clean

fclean		: clean
			$(RM) $(NAME)

re			: fclean all