# include "./solong.h"

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_game;

int	close_window_hook(t_game *game)
{
}

int main()
{
	ft_putendl_fd(" --- main functions --- ", STDOUT_FILENO);
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
