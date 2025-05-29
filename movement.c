#include "header.h"

static void recover_from_wall(t_game *game)
{
   for (double offset = 0.1; offset < 1.0; offset += 0.1)
   {
       for (int i = 0; i < 8; i++)
       {
           double angle = i * M_PI / 4;
           double test_x = game->px + cos(angle) * offset;
           double test_y = game->py + sin(angle) * offset;
           
           if (!is_wall(game, test_x, test_y))
           {
               game->px = test_x;
               game->py = test_y;
               return;
           }
       }
   }
}

void playermove(int keycode, t_game *game)
{
   double dx = 0, dy = 0;
   double move_speed = 0.1;
   double wall_buffer = 0.1;
   
   eval_keycode(keycode, game, &dx, &dy);
   
   double new_x = game->px + dx * move_speed;
   double new_y = game->py + dy * move_speed;
   
   try_open_door(game, new_x, new_y);
   try_move_axis(game, new_x, &game->px, wall_buffer, 1);
   try_move_axis(game, new_y, &game->py, wall_buffer, 0);
   
   if (is_wall(game, game->px, game->py))
       recover_from_wall(game);
}

void render(t_game *game)
{
   update_doors(game);
   ft_bzero(game->img_data, game->win_x * game->win_y * (game->bpp / 8));
   render_3d_projection(game);
   draw_minimap(game);
   draw_grid(game);
   draw_player(game);
   mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
}

int on_key_press(int keycode, void *param)
{
   t_game *game = (t_game *)param;
   
   if (keycode == XK_Escape)
       on_destroy(game);
   else if (keycode == XK_Left)
       rotate_player(game, -ROT_SPEED);
   else if (keycode == XK_Right)
       rotate_player(game, ROT_SPEED);
   else if (keycode == XK_w || keycode == XK_s || keycode == XK_a || keycode == XK_d)
       playermove(keycode, game);
   
   return 0;
}