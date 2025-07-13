# include "./solong.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

int	close_window_hook(t_game *game)
{
	ft_putendl_fd(" --- window close hook --- ",STDOUT_FILENO);
	if(game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);
}

int	key_press_hook(int keycode, t_game *game)
{
	ft_putendl_fd(" --- key press hook --- ",STDOUT_FILENO);
	if(keycode == 65307)	//Linux
	// if(keycode == 53)	//mac
	{
		ft_putendl_fd(" --- ESC key : window close hook --- ",STDOUT_FILENO);
		close_window_hook(game);
	}
	return 0;
}

int main()
{
	t_game game;

	ft_putendl_fd(" --- main functions --- ", STDOUT_FILENO);
	game.mlx_ptr = mlx_init();
	if(game.mlx_ptr == NULL)
		return(1);
	game.win_ptr = mlx_new_window(game.mlx_ptr, 800, 600, "STEP window");
	if(game.win_ptr == NULL)
		return(1);
	ft_putendl_fd(" --- open a window --- ", STDOUT_FILENO);
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	mlx_loop(game.mlx_ptr);
	return 0;
}









// int	main()
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
// 	return 0;
// }
