NAME = philo_one
DIRSRC = src
OBJD = obj
INCLUDE = head
OBJ			=	$(SRC:.c=.o)
OBJS		=	$(OBJ:%=$(OBJD)/%)

SRC = 	routine.c \
		extern.c \
		philo1.c \
		utils.c


CFLAGS		=	-Wall -Wextra -Werror
CC			=	clang

all : $(OBJD) $(OBJS)
	$(CC) $(CFLAGS) -lpthread -pthread -I ./ -o $(NAME) $(OBJS) $(LIB)

$(OBJD)	:
		@mkdir $(OBJD)

$(OBJD)/%.o	:	$(DIRSRC)/%.c
				$(CC) -I ./$(INCLUDE) $(CFLAGS) -o $@ -c $<


clean :
	rm -rf $(NAME)

fclean : clean
	rm -rf $(OBJD)