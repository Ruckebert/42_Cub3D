This file is a merged representation of a subset of the codebase, containing specifically included files, combined into a single document by Repomix.
The content has been processed where comments have been removed, empty lines have been removed.

# File Summary

## Purpose
This file contains a packed representation of the entire repository's contents.
It is designed to be easily consumable by AI systems for analysis, code review,
or other automated processes.

## File Format
The content is organized as follows:
1. This summary section
2. Repository information
3. Directory structure
4. Repository files (if enabled)
5. Multiple file entries, each consisting of:
  a. A header with the file path (## File: path/to/file)
  b. The full contents of the file in a code block

## Usage Guidelines
- This file should be treated as read-only. Any changes should be made to the
  original repository files, not this packed version.
- When processing this file, use the file path to distinguish
  between different files in the repository.
- Be aware that this file may contain sensitive information. Handle it with
  the same level of security as you would the original repository.

## Notes
- Some files may have been excluded based on .gitignore rules and Repomix's configuration
- Binary files are not included in this packed representation. Please refer to the Repository Structure section for a complete list of file paths, including binary files
- Only files matching these patterns are included: *.c
- Files matching patterns in .gitignore are excluded
- Files matching default ignore patterns are excluded
- Code comments have been removed from supported file types
- Empty lines have been removed from all files
- Files are sorted by Git change count (files with more changes are at the bottom)

# Directory Structure
```
door_wall.c
door_wall2.c
draw_grid.c
draw_grid2.c
draw.c
extractor.c
ft_atoi1.c
game_init.c
minimap.c
minimap2.c
minimap3.c
mlx_free.c
mlx_init.c
movement_utils.c
movement.c
movement2.c
ray_utils.c
ray_utils2.c
raycast.c
wall_render.c
wall_render2.c
wall_render3.c
```

# Files

## File: door_wall.c
```cpp
#include "../header.h"
static void	update_door_state(t_game *game, int x, int y)
{
	char	tile;
	int		is_adjacent;
	int		player_x;
	int		player_y;
	player_x = (int)floor(game->px);
	player_y = (int)floor(game->py);
	tile = game->core->map[y][x];
	is_adjacent = is_orthogonally_adjacent(player_x, player_y, x, y);
	if (tile == '2' && is_adjacent)
		game->core->map[y][x] = '3';
	else if (tile == '3' && !is_adjacent)
		game->core->map[y][x] = '2';
}
static void	process_row(t_game *game, int y)
{
	int	width;
	int	x;
	if (!game->core->map[y])
		return ;
	width = get_map_width(game->core->map, y);
	x = 0;
	while (x < width)
	{
		update_door_state(game, x, y);
		x++;
	}
}
void	update_doors(t_game *game)
{
	int	height;
	int	y;
	if (!game || !game->core || !game->core->map)
		return ;
	height = map_height(game->core->map);
	y = 0;
	while (y < height)
	{
		process_row(game, y);
		y++;
	}
}
int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;
	map_x = (int)floor(x);
	map_y = (int)floor(y);
	if (!is_valid_map_pos(game->core->map, map_x, map_y))
		return (1);
	if (game->core->map[map_y][map_x] == '1'
		|| game->core->map[map_y][map_x] == '2')
		return (1);
	return (0);
}
```

## File: door_wall2.c
```cpp
#include "../header.h"
int	is_orthogonally_adjacent(int px, int py, int x, int y)
{
	if ((abs(px - x) == 1 && py == y) || (abs(py - y) == 1 && px == x))
		return (1);
	return (0);
}
void	init_direction_arrays(int dx[4], int dy[4])
{
	dx[0] = 0;
	dx[1] = 1;
	dx[2] = 0;
	dx[3] = -1;
	dy[0] = -1;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = 0;
}
int	check_adjacent_tiles(t_game *game, int player_x, int player_y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	check_x;
	int	check_y;
	init_direction_arrays(dx, dy);
	i = 0;
	while (i < 4)
	{
		check_x = player_x + dx[i];
		check_y = player_y + dy[i];
		if (get_tile_at_pos(game->core->map, check_x, check_y) == '2')
			return (1);
		i++;
	}
	return (0);
}
```

## File: draw_grid.c
```cpp
#include "../header.h"
static void	draw_vertical_segment(t_game *game, int i, int j)
{
	t_line_points	pts;
	int				x;
	int				y;
	x = game->mini_off_x + j * game->m_sq_size;
	y = game->mini_off_y + i * game->m_sq_size;
	pts.x0 = x;
	pts.y0 = y;
	pts.x1 = x;
	pts.y1 = y + game->m_sq_size;
	draw_line(game, pts, 0x222222);
}
static void	process_vertical_lines(t_game *game, int i)
{
	int	j;
	int	cols;
	cols = ft_strlen(game->core->map[i]);
	j = 0;
	while (j <= cols)
	{
		if (tile_exists(game, i, j - 1) || tile_exists(game, i, j))
			draw_vertical_segment(game, i, j);
		j++;
	}
}
void	draw_vertical_grid_lines(t_game *game)
{
	int	i;
	int	rows;
	rows = map_height(game->core->map);
	i = 0;
	while (i < rows)
	{
		process_vertical_lines(game, i);
		i++;
	}
}
void	draw_grid(t_game *game)
{
	draw_vertical_grid_lines(game);
	draw_horizontal_grid_lines(game);
}
```

## File: draw_grid2.c
```cpp
#include "../header.h"
int	get_max_cols(t_game *game, int rows)
{
	int	i;
	int	max;
	int	cols;
	i = 0;
	max = 0;
	while (i < rows)
	{
		cols = ft_strlen(game->core->map[i]);
		if (cols > max)
			max = cols;
		i++;
	}
	return (max);
}
void	draw_horizontal_segment(t_game *game, int i, int j)
{
	t_line_points	pts;
	int				y;
	int				x;
	y = game->mini_off_y + i * game->m_sq_size;
	x = game->mini_off_x + j * game->m_sq_size;
	pts.x0 = x;
	pts.y0 = y;
	pts.x1 = x + game->m_sq_size;
	pts.y1 = y;
	draw_line(game, pts, 0x222222);
}
void	process_horizontal_lines(t_game *game, int i, int max_cols)
{
	int	j;
	j = 0;
	while (j < max_cols)
	{
		if (tile_exists(game, i - 1, j) || tile_exists(game, i, j))
			draw_horizontal_segment(game, i, j);
		j++;
	}
}
void	draw_horizontal_grid_lines(t_game *game)
{
	int	i;
	int	rows;
	int	max_cols;
	rows = map_height(game->core->map);
	max_cols = get_max_cols(game, rows);
	i = 0;
	while (i <= rows)
	{
		process_horizontal_lines(game, i, max_cols);
		i++;
	}
}
```

## File: draw.c
```cpp
#include "../header.h"
void	draw_player_icon(t_game *game, t_pos pos, int size)
{
	fill_tile(game, pos, size, 0xFF0000);
}
void	draw_player_direction_arrow(t_game *game, t_pos center)
{
	t_line_points	pts;
	int				len;
	len = game->m_sq_size / 2;
	pts.x0 = center.x;
	pts.y0 = center.y;
	pts.x1 = center.x + (int)(game->dir_x * len);
	pts.y1 = center.y + (int)(game->dir_y * len);
	draw_line(game, pts, 0x0000FF);
}
void	draw_player(t_game *game)
{
	int		margin;
	int		size;
	t_pos	center;
	t_pos	icon;
	margin = game->m_sq_size / 4;
	size = game->m_sq_size - (2 * margin);
	center = get_player_screen_pos(game);
	icon.x = center.x - size / 2;
	icon.y = center.y - size / 2;
	draw_player_icon(game, icon, size);
	draw_player_direction_arrow(game, center);
}
```

## File: extractor.c
```cpp
#include "../header.h"
void	extracting_link(char **core)
{
	char	*str;
	char	*temp;
	str = NULL;
	temp = NULL;
	str = ft_strchr(*core, ' ');
	if (str != NULL)
		str++;
	temp = ft_strdup(str);
	free(*core);
	*core = ft_strdup(temp);
	free(temp);
}
void	valid_file_checker(char *str, t_data *core)
{
	int	fd;
	fd = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		error_exit(core, "Error\nInvalid Texture Files!\n");
	close(fd);
}
void	alllinkextractor(t_data *core)
{
	if (core->checker != 15)
		error_exit(core, "Error\nDub Or No Textures!\n");
	if (!core->north || !core->east || !core->south || !core->west)
		error_exit(core, "Error\nEmpty Textures!\n");
	extracting_link(&core->north);
	core->north[ft_strlen(core->north) - 1] = '\0';
	valid_file_checker(core->north, core);
	extracting_link(&core->south);
	core->south[ft_strlen(core->south) - 1] = '\0';
	valid_file_checker(core->south, core);
	extracting_link(&core->east);
	core->east[ft_strlen(core->east) - 1] = '\0';
	valid_file_checker(core->east, core);
	extracting_link(&core->west);
	core->west[ft_strlen(core->west) - 1] = '\0';
	valid_file_checker(core->west, core);
}
```

## File: ft_atoi1.c
```cpp
#include "../header.h"
int	ft_atoi1(const char *nptr)
{
	int				minus;
	unsigned long	num;
	long			n;
	n = 0;
	num = 0;
	minus = 1;
	while ((*nptr >= 9 && *nptr <= 13) || (*nptr == ' '))
		nptr++;
	if (*nptr == '-')
		minus = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		n = (n + *nptr - '0') * 10;
		num = (num + *nptr - '0') * 10;
		if ((num != (unsigned long)n) && (minus == -1))
			return (0);
		else if ((num != (unsigned long)n) && (minus == 1))
			return (-1);
		nptr++;
	}
	n /= 10;
	return ((int)(n * minus));
}
void	free_double_array(char **array)
{
	int	i;
	i = 0;
	if (array == NULL)
		return ;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned long	i;
	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
```

## File: game_init.c
```cpp
#include "../header.h"
void	eval_keycode(int keycode, t_game *game, double *dx, double *dy)
{
	*dx = 0;
	*dy = 0;
	if (keycode == XK_w)
	{
		*dx = game->dir_x;
		*dy = game->dir_y;
	}
	else if (keycode == XK_s)
	{
		*dx = -game->dir_x;
		*dy = -game->dir_y;
	}
	else if (keycode == XK_d)
	{
		*dx = -game->dir_y;
		*dy = game->dir_x;
	}
	else if (keycode == XK_a)
	{
		*dx = game->dir_y;
		*dy = -game->dir_x;
	}
}
void	init_minimap(t_data *core, t_game *game)
{
	int	rows;
	int	cols;
	rows = map_height(core->map);
	cols = 0;
	while (core->map[0][cols])
		cols++;
	game->m_sq_size = 7;
	game->mini_w = cols * game->m_sq_size;
	game->mini_h = rows * game->m_sq_size;
	game->mini_off_x = 0;
	game->mini_off_y = 0;
}
```

## File: minimap.c
```cpp
#include "../header.h"
void	draw_line(t_game *game, t_line_points pts, int color)
{
	t_line	line;
	int		i;
	init_line(&line, pts);
	if (line.steps == 0)
		return ;
	i = 0;
	while (i <= line.steps)
	{
		my_mlx_pixel_put(game, (int)line.x, (int)line.y, color);
		line.x += line.x_inc;
		line.y += line.y_inc;
		i++;
	}
}
int	tile_exists(t_game *game, int row, int col)
{
	int		rows;
	char	tile;
	int		cols;
	rows = map_height(game->core->map);
	if (row < 0 || row >= rows)
		return (0);
	cols = ft_strlen(game->core->map[row]);
	if (col < 0 || col >= cols)
		return (0);
	tile = game->core->map[row][col];
	return (tile != '\n' && tile != '\0');
}
void	draw_rays(t_game *game)
{
	double	start_angle;
	double	angle_step;
	double	ray_angle;
	int		i;
	double	fov;
	i = 0;
	fov = M_PI / 3;
	angle_step = fov / NUM_RAYS;
	start_angle = game->angle - (fov / 2);
	while (i < NUM_RAYS)
	{
		ray_angle = start_angle + i * angle_step;
		cast_ray_dda(game, ray_angle);
		i++;
	}
}
t_pos	get_player_screen_pos(t_game *game)
{
	t_pos	pos;
	pos.x = game->mini_off_x + (int)(game->px * game->m_sq_size);
	pos.y = game->mini_off_y + (int)(game->py * game->m_sq_size);
	return (pos);
}
int	minimap(t_game *game)
{
	draw_minimap(game);
	draw_grid(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
	return (0);
}
```

## File: minimap2.c
```cpp
#include "../header.h"
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || x >= game->win_x || y < 0 || y >= game->win_y)
		return ;
	dst = game->img_data + (y * game->line_len + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}
void	fill_tile(t_game *game, t_pos base, int tile_size, int color)
{
	int	x;
	int	y;
	y = 0;
	while (y < tile_size)
	{
		x = 0;
		while (x < tile_size)
		{
			my_mlx_pixel_put(game, base.x + x, base.y + y, color);
			x++;
		}
		y++;
	}
}
int	get_tile_color(char map_tile)
{
	if (map_tile == '1')
		return (0xFFFFFF);
	if (map_tile == '2')
		return (0xFF0000);
	if (map_tile == '3')
		return (0x00FF00);
	if (map_tile == '\n')
		return (0x00000000);
	return (0x888888);
}
t_pos	get_minimap_pos(t_game *game, int grid_x, int grid_y)
{
	t_pos	pos;
	pos.x = game->mini_off_x + grid_x * game->m_sq_size;
	pos.y = game->mini_off_y + grid_y * game->m_sq_size;
	return (pos);
}
void	draw_minimap(t_game *game)
{
	int	rows;
	int	i;
	int	j;
	rows = map_height(game->core->map);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < (int)ft_strlen(game->core->map[i]))
		{
			if (game->core->map[i][j] != '\n')
				fill_tile(game,
					get_minimap_pos(game, j, i),
					game->m_sq_size,
					get_tile_color(game->core->map[i][j]));
			j++;
		}
		i++;
	}
}
```

## File: minimap3.c
```cpp
#include "../header.h"
void	init_line(t_line *line, t_line_points pts)
{
	line->dx = pts.x1 - pts.x0;
	line->dy = pts.y1 - pts.y0;
	line->x = pts.x0;
	line->y = pts.y0;
	if (abs(line->dx) > abs(line->dy))
		line->steps = abs(line->dx);
	else
		line->steps = abs(line->dy);
	if (line->steps == 0)
	{
		line->x_inc = 0;
		line->y_inc = 0;
	}
	else
	{
		line->x_inc = (float)line->dx / line->steps;
		line->y_inc = (float)line->dy / line->steps;
	}
}
```

## File: mlx_free.c
```cpp
#include "../header.h"
static void	destroy_images(t_game *game)
{
	if (game->tex_north.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_north.img);
	if (game->tex_south.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_south.img);
	if (game->tex_east.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_east.img);
	if (game->tex_west.img)
		mlx_destroy_image(game->mlx_ptr, game->tex_west.img);
	if (game->img)
		mlx_destroy_image(game->mlx_ptr, game->img);
}
static void	destroy_window_and_display(t_game *game)
{
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
static void	free_core_data(t_data *core)
{
	if (!core)
		return ;
	if (core->map)
		free_array(core->map);
	if (core->north)
		free(core->north);
	if (core->south)
		free(core->south);
	if (core->east)
		free(core->east);
	if (core->west)
		free(core->west);
}
int	on_destroy(t_game *game)
{
	t_data	*core;
	core = game->core;
	destroy_images(game);
	destroy_window_and_display(game);
	free_core_data(core);
	exit(0);
	return (0);
}
```

## File: mlx_init.c
```cpp
#include "../header.h"
static void	init_dir(t_data *core, t_game *game)
{
	if (core->dir == 'E')
		game->angle = 0.0;
	else if (core->dir == 'S')
		game->angle = M_PI / 2;
	else if (core->dir == 'W')
		game->angle = M_PI;
	else if (core->dir == 'N')
		game->angle = 3 * M_PI / 2;
	game->dir_x = cos(game->angle);
	game->dir_y = sin(game->angle);
}
static int	init_window(t_game *game)
{
	game->win_x = WIDTH;
	game->win_y = HEIGHT;
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->win_x,
			game->win_y, "so_long_with_extrasteps");
	if (!game->win_ptr)
		return (1);
	game->img = mlx_new_image(game->mlx_ptr, game->win_x, game->win_y);
	game->img_data = mlx_get_data_addr(game->img, &game->bpp,
			&game->line_len, &game->endian);
	return (0);
}
static int	load_textures(t_data *core, t_game *game)
{
	int	w;
	int	h;
	game->tex_north.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->north, &w, &h);
	game->tex_south.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->south, &w, &h);
	game->tex_east.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->east, &w, &h);
	game->tex_west.img = mlx_xpm_file_to_image(game->mlx_ptr,
			core->west, &w, &h);
	if (!game->tex_west.img || !game->tex_east.img
		|| !game->tex_south.img || !game->tex_north.img)
		return (1);
	game->tex_north.width = w;
	game->tex_north.height = h;
	game->tex_south.width = w;
	game->tex_south.height = h;
	game->tex_east.width = w;
	game->tex_east.height = h;
	game->tex_west.width = w;
	game->tex_west.height = h;
	return (0);
}
static void	load_texture_data(t_game *game)
{
	game->tex_north.data = mlx_get_data_addr(game->tex_north.img,
			&game->tex_north.bpp, &game->tex_north.line_len,
			&game->tex_north.endian);
	game->tex_south.data = mlx_get_data_addr(game->tex_south.img,
			&game->tex_south.bpp, &game->tex_south.line_len,
			&game->tex_south.endian);
	game->tex_east.data = mlx_get_data_addr(game->tex_east.img,
			&game->tex_east.bpp, &game->tex_east.line_len,
			&game->tex_east.endian);
	game->tex_west.data = mlx_get_data_addr(game->tex_west.img,
			&game->tex_west.bpp, &game->tex_west.line_len,
			&game->tex_west.endian);
}
int	init(t_data *core, t_game *game)
{
	game->core = core;
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1);
	game->px += 0.5;
	game->py += 0.5;
	init_dir(core, game);
	if (init_window(game))
		return (1);
	if (load_textures(core, game))
		return (1);
	load_texture_data(game);
	init_minimap(core, game);
	return (0);
}
```

## File: movement_utils.c
```cpp
#include "../header.h"
static void	normalize_angle(double *angle)
{
	while (*angle < 0)
		*angle += 2 * M_PI;
	while (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
}
void	rotate_player(t_game *game, double delta)
{
	game->angle += delta;
	normalize_angle(&game->angle);
	game->dir_x = cos(game->angle);
	game->dir_y = sin(game->angle);
}
void	try_open_door(t_game *game, double x, double y)
{
	char	tile;
	int		map_x;
	int		map_y;
	map_x = (int)floor(x);
	map_y = (int)floor(y);
	tile = get_tile_at_pos(game->core->map, map_x, map_y);
	if (tile == '2')
		game->core->map[map_y][map_x] = '3';
}
int	can_move_to(t_game *game, double x, double y, double buffer)
{
	if (is_wall(game, x + buffer, y + buffer))
		return (0);
	if (is_wall(game, x + buffer, y - buffer))
		return (0);
	if (is_wall(game, x - buffer, y + buffer))
		return (0);
	if (is_wall(game, x - buffer, y - buffer))
		return (0);
	return (1);
}
```

## File: movement.c
```cpp
#include "../header.h"
void	recover_from_wall(t_game *game)
{
	double	offset;
	int		i;
	double	angle;
	double	test_x;
	double	test_y;
	offset = 0.1;
	while (offset < 1.0)
	{
		i = 0;
		while (i < 8)
		{
			angle = i * M_PI / 4;
			test_x = game->px + cos(angle) * offset;
			test_y = game->py + sin(angle) * offset;
			if (!is_wall(game, test_x, test_y))
			{
				game->px = test_x;
				game->py = test_y;
				return ;
			}
			i++;
		}
		offset += 0.1;
	}
}
void	playermove(int keycode, t_game *game)
{
	double	dx;
	double	dy;
	double	new_x;
	double	new_y;
	double	move_speed;
	dx = 0;
	dy = 0;
	move_speed = 0.1;
	eval_keycode(keycode, game, &dx, &dy);
	new_x = game->px + dx * move_speed;
	new_y = game->py + dy * move_speed;
	try_open_door(game, new_x, new_y);
	try_move_x(game, new_x, 0.1);
	try_move_y(game, new_y, 0.1);
	if (is_wall(game, game->px, game->py))
		recover_from_wall(game);
}
void	render(t_game *game)
{
	update_doors(game);
	ft_bzero(game->img_data, game->win_x * game->win_y * (game->bpp / 8));
	render_3d_projection(game);
	draw_minimap(game);
	draw_grid(game);
	draw_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
}
int	on_key_press(int keycode, void *param)
{
	t_game	*game;
	double	rot_speed;
	game = (t_game *)param;
	rot_speed = M_PI / 16;
	if (keycode == XK_Escape)
		on_destroy(game);
	else if (keycode == XK_Left)
		rotate_player(game, -rot_speed);
	else if (keycode == XK_Right)
		rotate_player(game, rot_speed);
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		playermove(keycode, game);
	return (0);
}
```

## File: movement2.c
```cpp
#include "../header.h"
void	try_move_to(t_game *game, double new_x, double new_y, double buffer)
{
	if (can_move_to(game, new_x, new_y, buffer))
	{
		game->px = new_x;
		game->py = new_y;
	}
}
void	try_move_x(t_game *game, double new_x, double buffer)
{
	if (can_move_to(game, new_x, game->py, buffer))
		game->px = new_x;
}
void	try_move_y(t_game *game, double new_y, double buffer)
{
	if (can_move_to(game, game->px, new_y, buffer))
		game->py = new_y;
}
```

## File: ray_utils.c
```cpp
#include "../header.h"
t_ray	init_ray_values(double ray_angle)
{
	t_ray	ray;
	ray.dir_x = cos(ray_angle);
	ray.dir_y = sin(ray_angle);
	ray.delta_x = fabs(1.0 / ray.dir_x);
	ray.delta_y = fabs(1.0 / ray.dir_y);
	return (ray);
}
t_dda	init_step_and_sidedist(t_ray ray, double px, double py)
{
	t_dda	dda;
	dda.map_x = (int)px;
	dda.map_y = (int)py;
	if (ray.dir_x < 0.0)
	{
		dda.step_x = -1;
		dda.side_x = (px - dda.map_x) * ray.delta_x;
	}
	else
	{
		dda.step_x = 1;
		dda.side_x = (dda.map_x + 1.0 - px) * ray.delta_x;
	}
	if (ray.dir_y < 0.0)
	{
		dda.step_y = -1;
		dda.side_y = (py - dda.map_y) * ray.delta_y;
	}
	else
	{
		dda.step_y = 1;
		dda.side_y = (dda.map_y + 1.0 - py) * ray.delta_y;
	}
	return (dda);
}
double	correct_fisheye(double ray_angle, double player_angle,
			double perp_dist)
{
	double	angle_diff;
	angle_diff = ray_angle - player_angle;
	while (angle_diff > M_PI)
		angle_diff -= 2 * M_PI;
	while (angle_diff < -M_PI)
		angle_diff += 2 * M_PI;
	return (perp_dist * cos(angle_diff));
}
```

## File: ray_utils2.c
```cpp
#include "../header.h"
static int	get_map_dimensions(char **map, int y, int *height)
{
	if (y == 0)
	{
		*height = 0;
		while (map[*height])
			(*height)++;
	}
	if (map == NULL || map[y] == NULL)
		return (0);
	return ((int)ft_strlen(map[y]));
}
void	update_dda(t_ray ray, t_dda *dda)
{
	if (dda->side_x < dda->side_y)
	{
		dda->side_x += ray.delta_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_y += ray.delta_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}
void	perform_dda(t_game *game, t_ray ray, t_dda *dda)
{
	int		hit;
	int		depth;
	int		map_h;
	char	t;
	hit = 0;
	depth = MAX_DEPTH;
	map_h = 0;
	get_map_dimensions(game->core->map, 0, &map_h);
	while (!hit && depth-- > 0)
	{
		update_dda(ray, dda);
		if (!is_valid_map_pos(game->core->map, dda->map_x, dda->map_y))
			break ;
		t = game->core->map[dda->map_y][dda->map_x];
		if (t == '1' || t == '2')
			hit = 1;
	}
	if (dda->side == 0)
		dda->perp_dist = dda->side_x - ray.delta_x;
	else
		dda->perp_dist = dda->side_y - ray.delta_y;
}
```

## File: raycast.c
```cpp
#include "../header.h"
static t_raycast_result	cast_single_ray(t_game *game, double ray_angle)
{
	t_raycast_result	r;
	r.ray = init_ray_values(ray_angle);
	r.dda = init_step_and_sidedist(r.ray, game->px, game->py);
	perform_dda(game, r.ray, &r.dda);
	r.tile_type = get_tile_at_pos(game->core->map,
			r.dda.map_x, r.dda.map_y);
	r.corrected_dist = correct_fisheye(ray_angle,
			game->angle, r.dda.perp_dist);
	return (r);
}
void	process_column(t_game *game, int col, double ray_angle)
{
	t_raycast_result	r;
	t_wall_params		p;
	r = cast_single_ray(game, ray_angle);
	p = compute_wall_params(game, &r);
	draw_ceiling(game, col, p.start);
	draw_textured_wall(game, col, &p);
	draw_floor(game, col, p.end);
}
void	render_3d_projection(t_game *game)
{
	double	start_ang;
	double	step;
	double	fov;
	int		col;
	fov = M_PI / 3;
	start_ang = game->angle - (fov / 2.0);
	step = fov / (double)game->win_x;
	col = 0;
	while (col < game->win_x)
	{
		process_column(game, col, start_ang + col * step);
		col++;
	}
}
void	cast_ray_dda(t_game *game, double ray_angle)
{
	t_raycast_result	r;
	t_line_points		pts;
	int					ex;
	int					ey;
	r = cast_single_ray(game, ray_angle);
	ex = (int)((game->px + r.ray.dir_x * r.dda.perp_dist)
			* game->m_sq_size);
	ey = (int)((game->py + r.ray.dir_y * r.dda.perp_dist)
			* game->m_sq_size);
	pts.x0 = (int)(game->px * game->m_sq_size + game->m_sq_size / 2);
	pts.y0 = (int)(game->py * game->m_sq_size + game->m_sq_size / 2);
	pts.x1 = ex;
	pts.y1 = ey;
	draw_line(game, pts, 0x00FF00);
}
```

## File: wall_render.c
```cpp
#include "../header.h"
void	draw_floor(t_game *game, int col, int end)
{
	int	y;
	y = end + 1;
	while (y < game->win_y)
	{
		my_mlx_pixel_put(game, col, y, game->core->bottom);
		y++;
	}
}
static int	calculate_tex_y(int y, t_wall_params *p)
{
	int	off;
	int	tex_y;
	off = y - p->original_start;
	tex_y = (off * p->tex->height) / p->wall_height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= p->tex->height)
		tex_y = p->tex->height - 1;
	return (tex_y);
}
void	draw_textured_wall(t_game *game, int col, t_wall_params *p)
{
	int	y;
	int	tex_y;
	y = p->start;
	while (y <= p->end)
	{
		tex_y = calculate_tex_y(y, p);
		my_mlx_pixel_put(game, col, y,
			get_texture_pixel(p->tex, p->tex_x, tex_y));
		y++;
	}
}
```

## File: wall_render2.c
```cpp
#include "../header.h"
static int	calculate_slice_height(t_game *game, double corr_dist)
{
	double	proj_dist;
	int		slice_h;
	double	fov;
	fov = M_PI / 3;
	proj_dist = (game->win_x / 2.0) / tan(fov / 2.0);
	slice_h = (int)(proj_dist / corr_dist);
	return (slice_h);
}
static void	set_bounds(int *start, int *end, int slice_h, t_game *game)
{
	*start = (game->win_y / 2) - (slice_h / 2);
	*end = *start + slice_h;
	if (*start < 0)
		*start = 0;
	if (*end >= game->win_y)
		*end = game->win_y - 1;
}
void	compute_wall_dimensions(t_game *game, double corr_dist,
		int *start, int *end)
{
	int	slice_h;
	slice_h = calculate_slice_height(game, corr_dist);
	set_bounds(start, end, slice_h, game);
}
t_texture	*select_wall_texture(t_game *game, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
	{
		if (ray->dir_x > 0.0)
			return (&game->tex_east);
		else
			return (&game->tex_west);
	}
	if (ray->dir_y > 0.0)
		return (&game->tex_south);
	else
		return (&game->tex_north);
}
double	get_wall_x(t_game *game, t_ray *ray, t_dda *dda)
{
	double	wall_x;
	if (dda->side == 0)
		wall_x = game->py + dda->perp_dist * ray->dir_y;
	else
		wall_x = game->px + dda->perp_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
```

## File: wall_render3.c
```cpp
#include "../header.h"
int	compute_texture_x(t_game *game, t_ray *ray, t_dda *dda, t_texture *tex)
{
	double	wall_x;
	int		tex_x;
	wall_x = get_wall_x(game, ray, dda);
	tex_x = (int)(wall_x * tex->width);
	if ((dda->side == 0 && ray->dir_x < 0.0)
		|| (dda->side == 1 && ray->dir_y > 0.0))
		tex_x = tex->width - tex_x - 1;
	return (tex_x);
}
int	get_texture_pixel(t_texture *tex, int x, int y)
{
	int	offset;
	offset = y * tex->line_len + x * (tex->bpp / 8);
	return (*(int *)(tex->data + offset));
}
static void	set_wall_params_basic(t_wall_params *p, int start, int end)
{
	int	slice_h;
	slice_h = end - start;
	p->start = start;
	p->end = end;
	p->original_start = start;
	p->wall_height = slice_h;
}
t_wall_params	compute_wall_params(t_game *game, t_raycast_result *res)
{
	t_wall_params	p;
	int				start;
	int				end;
	compute_wall_dimensions(game, res->corrected_dist, &start, &end);
	set_wall_params_basic(&p, start, end);
	p.tex = select_wall_texture(game, &res->ray, &res->dda);
	p.tex_x = compute_texture_x(game, &res->ray, &res->dda, p.tex);
	return (p);
}
void	draw_ceiling(t_game *game, int col, int start)
{
	int	y;
	y = 0;
	while (y < start)
	{
		my_mlx_pixel_put(game, col, y, game->core->top);
		y++;
	}
}
```
