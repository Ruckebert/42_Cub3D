NAME = Cub3D

# Source and object files
SOURCE = main.c ft_atoi.c movement.c minimap.c mlx.c get_next_line.c get_next_line_utils.c parsing.c
OBJECTS = $(SOURCE:.c=.o)

# Compiler settings
CFLAGS = -Wall -Wextra -Werror -g
COMP = cc
RM = rm -f

# MiniLibX path (includes both lib and header)
MLX_PATH = mlx_linux

# Libft
LIBFT = ./libft/libft.a

all: $(NAME)

# Compile .c to .o
%.o: %.c
	$(COMP) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

# Final binary linking
$(NAME): $(OBJECTS)
	$(MAKE) -C ./libft --no-print-directory
	$(COMP) $(CFLAGS) $(OBJECTS) -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C ./libft --no-print-directory clean
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
