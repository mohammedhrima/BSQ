SRCS		= srcs/bsq.c srcs/map.c srcs/main.c srcs/read_next_line.c srcs/utils.c
INCLUDES	= includes
OBJS		= ${SRCS:.c=.o}
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O2
RM			= rm -f
NAME		= bsq

.c.o:
	${CC}  ${CFLAGS} -c $< -o ${<:.c=.o} -I${INCLUDES}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
