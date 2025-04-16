#ifndef HEADER_H
# define HEADER_H

# include "libft/libft.h"

/*Buffer for get next_line*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20000000000
# endif
# define HEIGHT 700
# define WIDTH 700
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data 
{
    char    **Map;      // Full Map
    int     Top;
    int     Bottom;     // r, g, b for ceiling and floor

    // File paths for the images
    char    *North;
    char    *South;
    char    *East;
    char    *West;

    int     error;

    int     px;
    int     py;
    char    dir;
} t_data;

typedef struct s_game
{
    t_data      *core;
    double      px;
    double      py;
    double      dir_x;
    double      dir_y;
    
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
    
    void        *minimap_img;
    void        *dynamic_img;
    char        *minimap_data;
    char        *dynamic_data;
    int         bpp, line_len, endian;
} t_game;

/* Parsing Functions */
int GetData(char *file, t_data *core);

/* Get_Next_Line */
char    *get_next_line(int fd, t_data *vars);
size_t  ft_strlen1(const char *str);
char    *ft_strchr1(const char *str, int c);
char    *ft_strjoin1(char const *s1, char const *s2);
char    *ft_strdup1(const char *src);

/* Gameloop-Minimap */
int init(t_data *core, t_game *game);
int minimap(t_game *game);
void draw_player(t_game *game);
void draw_minimap(t_game *game);
void draw_grid(t_game *game);

/* Movement */
void move(t_data *core, t_game *game);
int on_key_press(int keycode, void *data);

void    my_mlx_pixel_put(t_game *game, int x, int y, int color);

#endif
