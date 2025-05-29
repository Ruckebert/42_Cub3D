#include "header.h"

static int is_orthogonally_adjacent(int px, int py, int x, int y)
{
    return ((abs(px - x) == 1 && py == y) || (abs(py - y) == 1 && px == x));
}

int is_adjacent_to_door(t_game *game)
{
    int player_x = (int)floor(game->px);
    int player_y = (int)floor(game->py);
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    
    for (int i = 0; i < 4; i++)
    {
        int check_x = player_x + dx[i];
        int check_y = player_y + dy[i];
        
        if (get_tile_at_pos(game->core->map, check_x, check_y) == '2')
            return 1;
    }
    return 0;
}

void update_doors(t_game *game)
{
    int player_x = (int)floor(game->px);
    int player_y = (int)floor(game->py);
    int height = map_height(game->core->map);
    
    if (!game || !game->core || !game->core->map)
        return;
    
    for (int y = 0; y < height; y++)
    {
        if (!game->core->map[y])
            continue;
            
        int width = get_map_width(game->core->map, y);
        for (int x = 0; x < width; x++)
        {
            char tile = game->core->map[y][x];
            int is_adjacent = is_orthogonally_adjacent(player_x, player_y, x, y);
            
            if (tile == '2' && is_adjacent)
                game->core->map[y][x] = '3'; // Open door
            else if (tile == '3' && !is_adjacent)
                game->core->map[y][x] = '2'; // Close door
        }
    }
}

int is_wall(t_game *game, double x, double y)
{
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);
    
    if (!is_valid_map_pos(game->core->map, map_x, map_y))
        return 1;
    
    char tile = game->core->map[map_y][map_x];
    return (tile == '1' || tile == '2');
}