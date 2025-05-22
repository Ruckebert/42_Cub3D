#include "header.h"

int is_adjacent_to_door(t_game *game)
{
    int player_x = (int)floor(game->px);
    int player_y = (int)floor(game->py);
    int height = map_height(game->core->Map);
    
    // Only check the 4 orthogonal (non-diagonal) adjacent tiles
    // These are: North, East, South, West
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {-1, 0, 1, 0};
    
    for (int i = 0; i < 4; i++) {
        int check_x = player_x + dx[i];
        int check_y = player_y + dy[i];
        
        // Check map bounds
        if (check_y < 0 || check_y >= height)
            continue;
        
        // Make sure the row exists and has enough columns
        if (game->core->Map[check_y] == NULL)
            continue;
            
        int width = ft_strlen(game->core->Map[check_y]);
        if (check_x < 0 || check_x >= width)
            continue;
            
        // Check if this adjacent tile is a closed door
        if (game->core->Map[check_y][check_x] == '2')
            return 1;
    }
    return 0;
}

void update_doors(t_game *game)
{
    int player_x = (int)floor(game->px);
    int player_y = (int)floor(game->py);
    int height = map_height(game->core->Map);
    
    if (!game || !game->core || !game->core->Map)
        return;
    
    // Check all doors in the map
    for (int y = 0; y < height; y++) {
        // Make sure the row exists
        if (game->core->Map[y] == NULL)
            continue;
            
        int width = ft_strlen(game->core->Map[y]);
        for (int x = 0; x < width; x++) {
            // If this is a closed door
            if (game->core->Map[y][x] == '2') {
                // Check if player is orthogonally adjacent to this specific door
                // Only horizontally or vertically adjacent - not diagonally
                int is_adjacent = 0;
                
                // Check the 4 orthogonal directions
                if ((abs(player_x - x) == 1 && player_y == y) ||  // Horizontal adjacent
                    (abs(player_y - y) == 1 && player_x == x)) {  // Vertical adjacent
                    is_adjacent = 1;
                }
                
                if (is_adjacent) {
                    game->core->Map[y][x] = '3';  // Open the door
                }
            }
            // If this is an open door
            else if (game->core->Map[y][x] == '3') {
                // Check if player is still orthogonally adjacent
                int is_adjacent = 0;
                
                // Check the 4 orthogonal directions
                if ((abs(player_x - x) == 1 && player_y == y) ||  // Horizontal adjacent
                    (abs(player_y - y) == 1 && player_x == x)) {  // Vertical adjacent
                    is_adjacent = 1;
                }
                
                if (!is_adjacent) {
                    game->core->Map[y][x] = '2';  // Close the door
                }
            }
        }
    }
}
int is_wall(t_game *game, double x, double y)
{
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);
    int height = map_height(game->core->Map);
    
    if (map_y < 0 || map_y >= height)
        return 1;
        
    // Check if row exists
    if (game->core->Map[map_y] == NULL)
        return 1;
        
    int map_width = ft_strlen(game->core->Map[map_y]);
    if (map_x < 0 || map_x >= map_width)
        return 1;
        
    char tile = game->core->Map[map_y][map_x];
    
    // Only '1' (walls) and '2' (closed doors) block movement
    // '3' (open doors) should allow movement
    return (tile == '1' || tile == '2');
}