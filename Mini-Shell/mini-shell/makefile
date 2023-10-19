NAME		=	minishell

header	=	minishell.h

CC			=	gcc

# CFLAGS		=	" "

RM			=	rm -rf

SRCS		=	lib/ft_strlen.c lib/ft_strchr.c main.c 

OBJS		= $(SRCS:.c=.o)

$(NAME)		: $(OBJS) $(header)
			$(CC)  $(OBJS) -o $(NAME)

%o:%c $(header)
	$(CC) $(CFLAGS) -c $< -o $@

all			:	$(NAME)

cm			:	all clean
	
clean		:
			$(RM) $(OBJS)

mc			: all clean

fclean		: clean
			$(RM) $(NAME)

re			: fclean all