SRCS =	$(wildcard *.cpp)
OBJS = ${SRCS:.cpp=.o}

NAME = a.out

CC = c++

LINK = c++ -o

RM = rm -f

HEADER = -I include/

CFLAGS = -Werror -Wextra -Wall -std=c++98 -g
#-g -fsanitize=thread

.cpp.o: 
			${CC} ${CFLAGS} -c $< -o ${<:.cpp=.o} ${HEADER}

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
