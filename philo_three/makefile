NAME 		=	philo_three
DIRSRC 		=	src
OBJD 		=	obj
INCLUDE 	=	head
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(OBJD)/%)

SRC 		= 	routine.c \
				extern.c \
				philo_three.c \
				utils.c


CFLAGS		=	-pthread -Wall -Wextra -Werror #-g3 #-fsanitize=address #-march=native -pipe -O3
CC			=	clang

all : $(NAME)

$(NAME) 	: $(OBJD) $(OBJS)
			$(CC) $(CFLAGS) -lpthread -pthread -I ./ -o $(NAME) $(OBJS) $(LIB)

$(OBJD)	:
			@mkdir $(OBJD)

$(OBJD)/%.o	:	$(DIRSRC)/%.c
					$(CC) -I ./$(INCLUDE) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(NAME)

fclean : clean
	rm -rf $(OBJD)

re : fclean all

.PHONY : all clean fclean re