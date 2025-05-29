#include "header.h"

static void normalize_angle(double *angle)
{
   while (*angle < 0) *angle += 2 * M_PI;
   while (*angle >= 2 * M_PI) *angle -= 2 * M_PI;
}

void rotate_player(t_game *game, double delta)
{
   game->angle += delta;
   normalize_angle(&game->angle);
   game->dir_x = cos(game->angle);
   game->dir_y = sin(game->angle);
}

void try_open_door(t_game *game, double x, double y)
{
   char tile = get_tile_at_pos(game->core->map, (int)floor(x), (int)floor(y));
   if (tile == '2')
   {
       int map_x = (int)floor(x);
       int map_y = (int)floor(y);
       game->core->map[map_y][map_x] = '3';
       printf("Door opened at (%d, %d)\n", map_x, map_y);
   }
}

static int can_move_to(t_game *game, double x, double y, double buffer)
{
   return (!is_wall(game, x + buffer, y + buffer) &&
           !is_wall(game, x + buffer, y - buffer) &&
           !is_wall(game, x - buffer, y + buffer) &&
           !is_wall(game, x - buffer, y - buffer));
}

void try_move_axis(t_game *game, double new_pos, double *current_pos, 
                        double buffer, int is_x_axis)
{
   double test_x = is_x_axis ? new_pos : game->px;
   double test_y = is_x_axis ? game->py : new_pos;
   
   if (can_move_to(game, test_x, test_y, buffer))
       *current_pos = new_pos;
}