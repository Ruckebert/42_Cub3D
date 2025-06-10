NAME = cub3D

SOURCE = draw_grid2.c door_wall2.c minimap2.c minimap3.c ray_utils2.c movement2.c draw.c draw_grid.c mlx_init.c main.c map_utils.c map_checker.c get_next_line.c get_next_line_utils.c parsing.c utils.c mapcreator.c extractor.c ft_atoi1.c wall_render2.c wall_render3.c wall_render.c raycast.c ray_utils.c door_wall.c movement.c movement_utils.c minimap.c game_init.c mlx_free.c

OBJECTS = $(SOURCE:.c=.o)

# Compiler settings
CFLAGS = -Wall -Wextra -Werror -g
COMP = cc
RM = rm -f

# MiniLibX path (includes both lib and header)
MLX_PATH = mlx_linux

COMP = cc

# Libft
LIBFT = ./libft/libft.a

all: $(NAME)

# Compile .c to .o
%.o: %.c
	$(COMP) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

# Final binary linking
$(NAME): $(OBJECTS)
	$(MAKE) -C ./libft --no-print-directory
	$(COMP) $(CFLAGS) $(OBJECTS) -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C ./libft --no-print-directory clean
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
