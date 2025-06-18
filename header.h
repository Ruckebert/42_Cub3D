/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:57:24 by aruckenb          #+#    #+#             */
/*   Updated: 2025/06/18 13:18:38 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200000

# endif
# define HEIGHT 900
# define WIDTH 1800
# define RAY_LENGTH 1000
# define MAX_DEPTH 1000

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_line_points
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}	t_line_points;

typedef struct s_line
{
	int		dx;
	int		dy;
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
}	t_line;

typedef struct s_data
{
	char	**map;
	/* RGB Top&Bottom */
	int		top;
	int		bottom;
	/* Image Files */
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	/* Player Position&Direction */
	int		px;
	int		py;
	char	direction;
	/* Rest */
	int		error;
	int		checker;
	char	dir;
}	t_data;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_game
{
	t_data		*core;
	double		px;
	double		py;
	double		dir_x;
	double		dir_y;
	double		angle;
	int			m_sq_size;
	int			pdir;
	/* Mlx */
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_x;
	int			win_y;
	/* Image Data */
	void		*img;
	char		*img_data;
	int			bpp;
	int			line_len;
	int			endian;
	/* minimap geometry, in pixels */
	int			mini_off_x;
	int			mini_off_y;
	/* Textures */
	t_texture	tex_north;
	t_texture	tex_south;
	t_texture	tex_east;
	t_texture	tex_west;
}	t_game;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_y;
	double	delta_x;
}	t_ray;

typedef struct s_dda
{
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	int		side;
	double	perp_dist;
}	t_dda;

typedef struct s_raycast_result
{
	t_ray	ray;
	t_dda	dda;
	double	corrected_dist;
}	t_raycast_result;

typedef struct s_wall_params
{
	int			start;
	int			end;
	int			original_start;
	int			wall_height;
	t_texture	*tex;
	int			tex_x;
}	t_wall_params;

/*Parsing && Map Functions*/
int				getdata(char *file, t_data *core, unsigned int count);
char			**get_map_char_len(int map_size, char *str, t_data *vars);
void			alllinkextractor(t_data *core);
void			map_checker(t_data *core);
void			validplayerdata(t_data *core);
int				is_walkable(char c);
int				is_space(char c);
int				is_out_of_bounds(char **map, int i, int j);
void			assign_values(int dir[4][2]);
int				rgbloop(char *line, int i, int *type);
int				rgbfirst(char *line, int i);

/* Get_Next_Line */
char			*get_next_line(int fd, t_data *vars);
size_t			ft_strlen1(const char *str);
char			*ft_strchr1(const char *str, int c);
char			*ft_strjoin1(char const *s1, char const *s2);
char			*ft_strdup1(const char *src);

/* Gameloop-Minimap */
int				init(t_data *core, t_game *game);
void			render(t_game *game);
void			draw_player(t_game *game);
void			draw_minimap(t_game *game);
void			draw_grid(t_game *game);
void			draw_line(t_game *game, t_line_points pts, int color);
void			render_3d_projection(t_game *game);
int				map_height(char **map);
int				on_destroy(t_game *game);
void			eval_keycode(int keycode, t_game *game, double *dx, double *dy);
int				tile_exists(t_game *game, int row, int col);
void			fill_tile(t_game *game, t_pos base, int tile_size, int color);
t_pos			get_player_screen_pos(t_game *game);
void			load_texture_data(t_game *game);

/*Map utils*/
char			get_tile_at_pos(char **map, int x, int y);
int				is_valid_map_pos(char **map, int x, int y);
int				get_map_width(char **map, int y);
void			init_minimap(t_data *core, t_game *game);

/*Move utils*/
void			try_open_door(t_game *game, double x, double y);
void			rotate_player(t_game *game, double delta);
void			try_move_x(t_game *game, double new_x, double buffer);
void			try_move_y(t_game *game, double new_y, double buffer);

/*Wall,Door*/
int				is_wall(t_game *game, double x, double y);
void			update_doors(t_game *game);
int				is_orthogonally_adjacent(int px, int py, int x, int y);
void			draw_horizontal_grid_lines(t_game *game);
void			compute_wall_dimensions(t_game *game, double corr_dist,
					int *start, int *end);
t_texture		*select_wall_texture(t_game *game, t_ray *ray, t_dda *dda);
double			get_wall_x(t_game *game, t_ray *ray, t_dda *dda);
int				get_texture_pixel(t_texture *tex, int x, int y);

/* Movement */
void			move(t_data *core, t_game *game);
int				on_key_press(int keycode, void *data);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);

/*Utils Function*/
void			free_array(char **example);
char			*ft_strcpy(char *dest, char *src);
void			map_error(int fd, char *str);
void			error_exit(t_data *core, const char *msg);
int				ft_atoi1(const char *nptr);
int				can_move_to(t_game *game, double x, double y, double buffer);

//raycast_utils
t_ray			init_ray_values(double ray_angle);
t_dda			init_step_and_sidedist(t_ray ray, double px, double py);
void			perform_dda(t_game *game, t_ray ray, t_dda *dda);
double			correct_fisheye(double ray_angle, double player_angle,
					double perp_dist);
t_wall_params	compute_wall_params(t_game *game, t_raycast_result *res);
void			draw_ceiling(t_game *game, int col, int start);
void			draw_floor(t_game *game, int col, int end);
void			draw_textured_wall(t_game *game, int col, t_wall_params *p);
void			init_line(t_line *line, t_line_points pts);

#endif
