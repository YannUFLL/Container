SRCS =	$(wildcard */*.cpp)
OBJS = ${addprefix objs/, $(notdir $(SRCS:.cpp=.o))}

NAME = a.out

NAME_STD = std.out

NAME_FT = ft.out

CC = c++

LINK = c++ -o

RM = rm -f

DEBEUG = -g

CFLAGS = -Werror -Wextra -Wall -std=c++98 -g3

objs/%.o: */%.cpp
	${CC} -o $@ -c $< ${CFLAGS} ${DEBEUG}


${NAME}:	${OBJS}
			${LINK} ${NAME} ${OBJS} -fsanitize=thread

${NAME_STD}:	${OBJS}
				${LINK} ${NAME_STD} ${OBJS} -fsanitize=thread

${NAME_FT}:	${OBJS}
			${LINK} ${NAME_FT} ${OBJS} -fsanitize=thread

ft_mode : 
			sed -i.bak 's/std/ft/' test/test.hpp

std_mode : 
			sed -i.bak 's/ft/std/' test/test.hpp

all:		${NAME}

std:	clean std_mode ${NAME_STD}

ft: 	clean ft_mode ${NAME_FT}

clean:
			${RM} ${OBJS}

fclean:     clean
			${RM} ${NAME} ${NAME_STD} ${NAME_FT}

re:			fclean ft_mode all

.PHONY:		all clean fclean re std ft ft_mode std_mode
