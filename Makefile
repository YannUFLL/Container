SRCS =	$(wildcard */*.cpp)
OBJS = ${addprefix objs/, $(notdir $(SRCS:.cpp=.o))}

NAME = a.out

CC = c++

LINK = c++ -o

RM = rm -f

DEBEUG = -g

CFLAGS = -Werror -Wextra -Wall -std=c++98 
#-g -fsanitize=thread

objs/%.o: */%.cpp
	${CC} -o $@ -c $< ${CFLAGS} ${DEBEUG}


${NAME}:	${OBJS}
			${LINK} ${NAME} ${OBJS} 
#-g -fsanitize=thread

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:     clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
