
/*
void	init_assets(t_data *core, t_game *game)
{
	
	game->img_N = mlx_png_file_to_image(game->mlx_ptr,
			core->North, 100,100);//&data->width, &data->height);
	game->img_S = mlx_png_file_to_image(game->mlx_ptr,
			core->South, 100,100);//&data->width, &data->height);
	game->img_W = mlx_png_file_to_image(game->mlx_ptr,
			core->West, 100,100);//&data->width, &data->height);
	game->img_E = mlx_png_file_to_image(game->mlx_ptr,
			core->East, 100,100);//&data->width, &data->height);
//	game->img_C = mlx_png_file_to_image(data->mlx_ptr,
//			data->player_path, &data->width, &data->height);

}


init(t_data *core, t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		return (1); 
	game->win_ptr = mlx_new_window(game->mlx_ptr,
		200, 200, "so_long_with_extrasteps");
	if (!game->win_ptr)
		return (1);
	init_assets(&core, &game);
}
*/