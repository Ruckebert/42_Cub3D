#include "header.h"
#include "libft/libft.h"

void DummySetter(t_data *core)
{
    // r, g, b = 170, 187, 204
    core->Top = 11189132;
    core->Bottom = 11189196;
    core->px = 26;
    core->py = 11;
    core->dir = 'E';
    // Put the image file here
    core->North = "~/Downloads/1.png";
    core->South = "~/Downloads/2.png";
    core->East = "~/Downloads/3.png";
    core->West = "~/Downloads/4.png";
    
    // Allocate 15 pointers (the 15th is left as NULL)
    core->Map = calloc(15, sizeof(char *));
    core->Map[0] = "        1111111111111111111111111";
    core->Map[1] = "        1000000000110000000000001";
    core->Map[2] = "        1000000000110000000000001";
    core->Map[3] = "        1001000000000000000000001";
    core->Map[4] = "111111111011000001110000000000001";
    core->Map[5] = "100000000011000001110111112111111";
    core->Map[6] = "11110111111111011100000010001";
    core->Map[7] = "11110111111111011101010010001";
    core->Map[8] = "11000000110101011100000010001";
    core->Map[9] = "10000000000000001100000010001";
    core->Map[10] = "10000000000000001101010010001";
    core->Map[11] = "11000001110101011111011110N0111";
    core->Map[12] = "11110111 1110101 101111010001";
    core->Map[13] = "11111111 1111111 111111111111";
}

int on_window_close(void *param)
{
    t_game *game = (t_game *)param;
    on_destroy(game);
    return (0);
}

int main(int argc, char **argv)
{
    t_data core;
    t_game game;
    (void) argv;
    
    ft_bzero(&core, sizeof(core));
    if (argc != 2)
    {
        write(2, "Not the correct amount of arguments\n", 37);
        return (-1);
    }
    // Uncomment if you use file parsing:
    // if (GetData(argv[1], &core) == -1)
    //     return (1);
    
    DummySetter(&core);
    game.px = core.px;
    game.py = core.py;
    init(&core, &game);
    render(&game);
    
    mlx_loop_hook(game.mlx_ptr, (void *)render, &game);
    mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &on_key_press, &game);
    
    // Add this line to handle window close event (X button)
    mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, &on_window_close, &game);
    
    mlx_loop(game.mlx_ptr);
}
