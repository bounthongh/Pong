CC	=	gcc

NAME	=	pong

SRC	=	src/main.c          \
	    	src/menuGTK.c       \
	    	src/gameSDL.c	\
		src/reseau/select/send.c	\
		src/reseau/select/recv.c


OBJ	=	$(SRC:%.c=%.o)
RM	=	rm -f
CFLAGS	=	-I./header -g3 -W -Wall -Werror `pkg-config --cflags --libs gtk+-2.0`
GTKFLAGS	= `pkg-config --libs gtk+-2.0`
LDFLAGS	=	-lSDL2 -lSDL2_image

$(NAME):	$(OBJ)
		$(CC) $(GTKFLAGS) $(OBJ) -lpthread -o $(NAME)  $(LDFLAGS) $(GTKFLAGS)

all:	$(NAME)

clean:
	$(RM) $(OBJ) pong

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
