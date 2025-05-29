/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marsenij <marsenij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 08:57:24 by aruckenb          #+#    #+#             */
/*   Updated: 2025/05/27 12:49:24 by marsenij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"

/*Buffer for get next_line*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200000

# endif
# define ROT_SPEED (M_PI/16)
# define HEIGHT 900
# define WIDTH 1800
# define NUM_RAYS 100
# define FOV (M_PI / 3)  // 60 degrees
# define RAY_LENGTH 1000
# define MAX_DEPTH 1000
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_pos {
    int x;
    int y;
} t_pos;


typedef struct s_line {
    int dx;
    int dy;
    int steps;
    float x_inc;
    float y_inc;
    float x;
    float y;
} t_line;

typedef struct s_data
{

	char	**map;		//Full Map
	int		top;
	int		bottom; //This contains the rbg for the ceiling and floor

	//These char contain the file path for the images
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	
	int	px;
	int	py;
	
	char	direction;
	int		error;
	int		checker;
    char    dir;

} t_data;

typedef struct s_texture
{
    void *img;
    char *data;
    int width;
    int height;
    int bpp;
    int line_len;
    int endian;
} t_texture;

typedef struct s_game
{
    t_data      *core;
    double      px;
    double      py;
    double      dir_x;
    double      dir_y;
    double      angle;

    int         m_sq_size;
    int         pdir;
    
    void        *mlx_ptr;
    void        *win_ptr;
    int         win_x;
    int         win_y;  
    
    void        *img_N;
    void        *img_S;
    void        *img_W;
    void        *img_E;
    
    void        *img_C;
    void        *img_F;
    
    void        *img;
    char        *img_data;
    int         bpp, line_len, endian;

    /* minimap geometry, in pixels */
    int         mini_w;
    int         mini_h;
    int         mini_off_x;
    int         mini_off_y;

    t_texture tex_north;
    t_texture tex_south;
    t_texture tex_east;
    t_texture tex_west;
} t_game;

typedef struct s_ray {
    double dir_x, dir_y;
    double delta_x, delta_y;
} t_ray;

typedef struct s_dda {
    int   step_x,    step_y;
    int   map_x,     map_y;
    double side_x,   side_y;
    int   side;
    double perp_dist;
} t_dda;

typedef struct s_raycast_result
{
    t_ray ray;
    t_dda dda;
    char tile_type;
    double corrected_dist;
} t_raycast_result;

typedef struct s_wall_params
{
    int start;
    int end;
    t_texture *tex;
    int tex_x;
} t_wall_params;

/*Parsing && Map Functions*/
int		getdata(char *file, t_data *core, unsigned int	count);
char	**get_map_char_len(int map_size, char *str, t_data *vars);
void	alllinkextractor(t_data *core);
void	map_checker(t_data *core);

/* Get_Next_Line */
char    *get_next_line(int fd, t_data *vars);
size_t  ft_strlen1(const char *str);
char    *ft_strchr1(const char *str, int c);
char    *ft_strjoin1(char const *s1, char const *s2);
char    *ft_strdup1(const char *src);

/* Gameloop-Minimap */
int init(t_data *core, t_game *game);
void render(t_game *game);
void draw_player(t_game *game);
void draw_minimap(t_game *game);
void draw_grid(t_game *game);
void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color);
void cast_ray_dda(t_game *game, double ray_angle);
void render_3d_projection(t_game *game);
int map_height(char **map);
int on_destroy(t_game *game);
void eval_keycode(int keycode, t_game *game, double *dx, double *dy);

/*Map utils*/
char get_tile_at_pos(char **map, int x, int y);
int is_valid_map_pos(char **map, int x, int y);
int get_map_width(char **map, int y);

/*Move utils*/
void try_open_door(t_game *game, double x, double y);
void try_move_axis(t_game *game, double new_pos, double *current_pos, double buffer, int is_x_axis);
void rotate_player(t_game *game, double delta);

/*Wall,Door*/
int is_wall(t_game *game, double x, double y);
void update_doors(t_game *game);

/* Movement */
void move(t_data *core, t_game *game);
int on_key_press(int keycode, void *data);
void    my_mlx_pixel_put(t_game *game, int x, int y, int color);

/*Utils Function*/
void	free_array(char **example);
char	*ft_strcpy(char *dest, char *src);
void	map_error(int fd, char *str);
void	error_exit(t_data *core, const char *msg);
int		ft_atoi1(const char *nptr);

#endif
