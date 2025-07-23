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
	int		player_pos_y;
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

// void	read_map_from_file(const char *file_path, t_map *map)
// {
// 	// char	*LINE;

// 	(void)file_path;
// 	map->data[0][0] = '1';
// 	map->data[0][1] = '0';
// 	map->data[0][2] = '\n';
// 	map->data[1][0] = 'C';
// 	map->data[1][1] = 'E';
// 	map->data[1][2] = '\0';
// }

void	free_double_ptr(char **ptr, size_t count)
{
	size_t	i;

	i = 0;
	if (count < 1)
		return ;
	while (i < count)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

char	**ft_stradd(char **double_array, char *new_str)
{
	char	**res;
	size_t	i;
	size_t	line_num;

	line_num = 0;
	while(double_array && double_array[line_num])
	{
		line_num++;
	}
	res = (char **)malloc(sizeof(char *) * (line_num + 2));
	if(!res)
	{
		return NULL;
	}
	i = 0;
	while(i < line_num)
	{
		res[i] = double_array[i];
		i++;
	}
	if (new_str)
	{
		res[i++] = new_str;
	}
	else
	{
		res[i++] = NULL;
	}
	res[i] = NULL;
	free(double_array);
	return(res);
}

void read_map_from_file(const char *file_path, t_game *game) // gameポインタを受け取るように変更
{
	(void)file_path;

    // // 実際はfile_pathからマップサイズを読み込み、それに基づいてdataを確保する
    // // ここでは仮に2x2のマップを想定してハードコード
    // game->map.width = 2;
    // game->map.height = 2;

    // // map->data (char**) のためのメモリを確保（行ポインタの配列）
    // game->map.data = (char **)malloc(sizeof(char *) * game->map.height);
    // if (!game->map.data)
    //     error_exit("Failed to allocate map rows");

    // int i = 0;
    // while (i < game->map.height)
    // {
    //     // 各行（char*）のためのメモリを確保
    //     // +1 はヌル終端文字のため (C文字列として扱う場合)
    //     game->map.data[i] = (char *)malloc(sizeof(char) * (game->map.width + 1));
    //     if (!game->map.data[i])
    //     {
    //         // 途中でメモリ確保失敗した場合、それまでに確保したメモリを解放する
    //         while (--i >= 0)
    //             free(game->map.data[i]);
    //         free(game->map.data);
    //         error_exit("Failed to allocate map columns");
    //     }
    //     i++;
    // }

    // // マップデータを代入 (ここをファイル読み込みロジックに置き換える)
    // game->map.data[0][0] = '1';
    // game->map.data[0][1] = '0';
    // game->map.data[0][2] = '\0'; // C文字列として終端

    // game->map.data[1][0] = 'P';
    // game->map.data[1][1] = 'E';
    // game->map.data[1][2] = '\0'; // C文字列として終端

	int fd;
	int i;
	char *tmp_line;

	fd = open("./map/test.ber", O_RDONLY);
	game->map.data = NULL;
	i = 0;

	while (1)
	{
		tmp_line = get_next_line(fd);
		ft_printf("	tmp_line:%s\n", tmp_line);
		
		game->map.data = ft_stradd(game->map.data, tmp_line);
		if(!tmp_line)
			break;
		ft_printf("	map.data:%s\n", game->map.data[i++]);
	}
	close(fd);

    game->map.width = ft_strlen(game->map.data[0]);
    game->map.height = i - 1;
	
	i = 0;

    // // プレイヤー位置など、他のマップ情報も設定
    // game->map.player_pos_x = 0; // 例
    // game->map.player_pos_y = 0; // 例
    // game->map.player_count = 1; // 例
    // game->map.exit_count = 1; // 例
    // game->map.collective_count = 1; // 例
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
	
	// //	step3
	// draw_stuff(&game);

	//	step4
	game.img_wall = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/wall.xpm", &game.img_width, &game.img_height);
    if (!game.img_wall)
		error_exit("Failed to load wall image");
    game.img_floor = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/floor.xpm", &game.img_width, &game.img_height);
    if (!game.img_floor)
		error_exit("Failed to load floor image");
    game.img_player = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/player.xpm", &game.img_width, &game.img_height);
    if (!game.img_player)
		error_exit("Failed to load player image");
    game.img_collectible = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/collectible.xpm", &game.img_width, &game.img_height);
    if (!game.img_collectible)
		error_exit("Failed to load collectible image");
    game.img_exit = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/exit.xpm", &game.img_width, &game.img_height);
    if (!game.img_exit)
		error_exit("Failed to load exit image");
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	
	// draw_image(&game);
	read_map_from_file("", &game);
	render_map(&game);
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
