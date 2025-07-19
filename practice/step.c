#include "./solong.h"

#define TILE_SIZE 32

void	error_exit(char *message)
{
	ft_putstr_fd(" --- error exit --- ", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
	int		player_count;
	int		exit_count;
	int		collective_count;
	int		player_pos_x;
	int		olayer_pos_y;
}			t_map;

// typedef	struct s_img
// {
// 	void	*wall_img;
// 	void	*floor_img;
// 	void	*player_img;
// 	void	*collectible_img;
// 	void	*exit_img;
// 	int		width;
// 	int		height;
// }	t_img;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	int		move_count;
	// t_img	img;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
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
	if (game->img_collectible)
	{
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
				game->img_collectible, 0, 0);
	}
	return (0);
}

void	read_map_from_file(const char *file_path, t_map *map)
{
	char	*LINE;
}

//	render map
int	render_map(t_game *game)
{
	int		x;
	int		y;
	void	*current_img;
	char	cell;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			cell = game->map.data[y][x];
			current_img = NULL;
			if (cell == '1')
			{
				current_img = game->img_wall;
			}
			else if (cell == '0')
			{
				current_img = game->img_floor;
			}
			else if (cell == 'P')
			{
				current_img = game->img_player;
			}
			else if (cell == 'C')
			{
				current_img = game->img_collectible;
			}
			else if (cell == 'E')
			{
				current_img = game->img_exit;
			}
			if (current_img)
			{
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
						current_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
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
	game.img_collectible = mlx_xpm_file_to_image(game.mlx_ptr,
			"./textures/collectible.xpm", &game.img_width, &game.img_height);
	draw_image(&game);
	mlx_loop(game.mlx_ptr); // what's this function ?
	if (game.img_collectible)
	{
		mlx_destroy_image(game.mlx_ptr, game.img_collectible);
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
