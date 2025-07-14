#include "./solong.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*my_image;
	int		img_width;
	int		img_height;
}			t_game;

//	step2
int	close_window_hook(t_game *game)
{
	ft_putendl_fd(" --- window close hook --- ", STDOUT_FILENO);
	if (game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

int	key_press_hook(int keycode, t_game *game)
{
	ft_putendl_fd(" --- key press hook --- ", STDOUT_FILENO);
	if (keycode == 65307) // Linux
	// if(keycode == 53)	//mac
	{
		ft_putendl_fd(" --- ESC key : window close hook --- ", STDOUT_FILENO);
		close_window_hook(game);
	}
	return (0);
}

//	step3
int	draw_stuff(t_game *game)
{
	int	i;
	int	j;

	mlx_pixel_put(game->mlx_ptr, game->win_ptr, 400, 300, 0XFF0000);
	i = 0;
	j = 0;
	while (i++ < 50)
	{
		while (j++ < 50)
		{
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, 100 + i, 100 + j,
				0x008800);
		}
		j = 0;
	}
	return (0);
}

// step4
int	draw_image(t_game *game)
{
	// mlx_clear_window(game->mlx_ptr, game->win_ptr);
	if (game->my_image)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->my_image, 0,
			0);
	}
	return (0);
}

int	main(void)
{
	t_game	game;

	ft_putendl_fd(" --- main functions --- ", STDOUT_FILENO);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (1);
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "STEP window");
	if (game.win_ptr == NULL)
		return (1);
	ft_putendl_fd(" --- open a window --- ", STDOUT_FILENO);
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	//	step3
	draw_stuff(&game);
	//	step4
	game.my_image = mlx_xpm_file_to_image(game.mlx_ptr, c, &game.img_width, &game.img_height);
	draw_image(&game);
	mlx_loop(game.mlx_ptr); // what's this function ?
	if (game.my_image)
	{
		mlx_destroy_image(game.mlx_ptr, game.my_image);
	}
	return (0);
}

// int	main(void)
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;

// 	mlx_ptr = mlx_init();
// 	if (mlx_ptr == NULL)
// 	{
// 		exit(1);
// 	}
// 	win_ptr = mlx_new_window(mlx_ptr, 800, 600,"step window" );
// 	if (win_ptr == NULL)
// 	{
// 		exit(1);
// 	}
// 	mlx_loop(mlx_ptr);
// 	return (0);
// }
