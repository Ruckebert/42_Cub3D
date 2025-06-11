NAME = cub3D

SOURCEPARSING = main.c Parsing/get_next_line.c Parsing/get_next_line_utils.c Parsing/map_checker.c Parsing/map_checker2.c Parsing/map_utils.c Parsing/mapcreator.c Parsing/parsing.c Parsing/utils.c Parsing/utils2.c

SOURCERAYCASTING = ImageRayCasting/door_wall.c ImageRayCasting/door_wall2.c ImageRayCasting/draw.c ImageRayCasting/draw_grid.c ImageRayCasting/draw_grid2.c ImageRayCasting/extractor.c ImageRayCasting/ft_atoi1.c ImageRayCasting/game_init.c ImageRayCasting/minimap.c ImageRayCasting/minimap2.c ImageRayCasting/minimap3.c ImageRayCasting/mlx_free.c ImageRayCasting/mlx_init.c ImageRayCasting/movement.c ImageRayCasting/movement2.c ImageRayCasting/movement_utils.c ImageRayCasting/raycast.c ImageRayCasting/ray_utils.c ImageRayCasting/ray_utils2.c ImageRayCasting/wall_render.c ImageRayCasting/wall_render2.c ImageRayCasting/wall_render3.c

OBJECTS = $(SOURCEPARSING:.c=.o)

OBJECTSRAYS = $(SOURCERAYCASTING:.c=.o)

CFLAGS = -Wall -Wextra -Werror -g
COMP = cc
RM = rm -f

MLX_PATH = mlx_linux

COMP = cc

LIBFT = ./libft/libft.a

all: $(NAME)

%.o: %.c
	$(COMP) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

$(NAME): $(OBJECTS) $(OBJECTSRAYS)
	$(MAKE) -C ./libft --no-print-directory
	$(COMP) $(CFLAGS) $(OBJECTS) $(OBJECTSRAYS) -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

clean:
	$(MAKE) -C ./libft --no-print-directory clean
	$(RM) $(OBJECTS) $(OBJECTSRAYS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
