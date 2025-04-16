
NAME = Cub3D

SOURCE = main.c ft_atoi.c movement.c minimap.c mlx.c get_next_line.c get_next_line_utils.c parsing.c

OBJECTS = $(SOURCE:.c=.o)

CFLAGS = -Werror -Wextra -g -Wall

COMP = cc

RM = rm -f

all: ${NAME}

.c.o:
	-cc ${CFLAGS}  -I/usr/include -Imlx_linux -c $< -o ${<:.c=.o} 

${NAME}: ${OBJECTS}
		${MAKE} -C ./libft --no-print-directory
		${COMP} ${CFLAGS} ${OBJECTS} -lmlx -lXext -lX11 -lm ./libft/libft.a -o ${NAME}

clean: 
	${MAKE} -C ./libft --no-print-directory fclean
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
