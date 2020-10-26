NAME		=	philo

DIRSRC		=	Src
OBJD		=	Obj
INCLUDE		=	Head
SUB_MAKE	=	Libft
LIB			=	$(SUB_MAKE)/libft.a

SRC			=	main.c 

OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(OBJD)/%)

CFLAGS		=	-g3 -fsanitize=address#-Wall -Wextra -Werror #-O3 -g3 -march=native -pipe

CC			=	clang
RM			=	rm -f
ECHO		=	echo

$(NAME)		:	$(LIB) $(OBJD) $(OBJS)
				@$(ECHO) "\033[32m> Minishell built\033[0m"
				@$(ECHO) "\033[38;5;208m> Compiling Minishell\033[38;5;125m"
				$(CC) -I./$(INCLUDE) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB)
				@$(ECHO) "\033[32m> Minishell compiled\033[0m"

$(LIB)		:
				@$(ECHO) "\033[38;5;208m> Compiling Libft\033[38;5;125m"
				@($(MAKE) -s -C $(SUB_MAKE))

$(OBJD)		:
				@mkdir $(OBJD)

$(OBJD)/%.o	:	$(DIRSRC)/%.c
				@$(ECHO) "\033[38;5;208m> Building Minishell\033[38;5;125m"
				$(CC) -I./$(INCLUDE) -I./$(SUB_MAKE) $(CFLAGS) -o $@ -c $<

all			:	$(NAME)

clean		:
				@($(MAKE) clean -s -C $(SUB_MAKE))
				@$(ECHO) "\033[94m> Libft Objects removed\033[0m"
				-@$(RM) $(OBJS)
				@$(ECHO) "\033[94m> Minishell Objects removed\033[0m"

fclean		:	clean
				@($(MAKE) fclean -s -C $(SUB_MAKE))
				@$(ECHO) "\033[94m> Libft cleaned all\033[0m"
				-@$(RM) $(NAME)
				@$(ECHO) "\033[94m> Minishell cleaned all\033[0m"

re			:	fclean all

.PHONY		:	all clean re fclean bonus minfclean reft