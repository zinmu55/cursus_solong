#include "./solong.h"

void	error_exit(char *message)
{
	ft_putstr_fd(" --- error exit --- ", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	my_print_map(char **mapdata)
{
	int	y;

	ft_printf(" --- Current Map State --- \n");
	y = 0;
	while (mapdata[y])
	{
		ft_printf("%s\n", mapdata[y]);
		y++;
	}
	ft_printf(" ------------------------- \n");
}

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
	if (keycode == KEY_ESC) // Linux
	// if (keycode == 65307) // Linux
	// if(keycode == 53)	//mac
	{
		ft_putendl_fd(" --- ESC key : window close hook --- ", STDOUT_FILENO);
		close_window_hook(game);
	}
	else if(keycode == KEY_W)
	{
		move_player(game, 0, -1);
	}
	else if(keycode == KEY_S)
	{
		move_player(game, 0, 1);
	}
	else if(keycode == KEY_A)
	{
		move_player(game, -1, 0);
	}
	else if(keycode == KEY_D)
	{
		move_player(game, 1, 0);
	}
	return (0);
}

void free_map_data(t_map *map)
{
	if (map->data)
	{
		free_double_ptr(map->data, map->height);
		map->data = NULL;
	}
}

void destroy_game_resources(t_game *game)
{
	if (game->img_wall)
		mlx_destroy_image(game->mlx_ptr, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx_ptr, game->img_floor);
	if (game->img_player)
		mlx_destroy_image(game->mlx_ptr, game->img_player);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx_ptr, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx_ptr, game->img_exit);
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);

	free_map_data(&(game->map));
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
			mlx_pixel_put(game->mlx_ptr, game->win_ptr, 100 + i, 100 + j, 0x008800);
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
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_collectible, 0, 0);
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
	while (double_array && double_array[line_num])
	{
		line_num++;
	}
	res = (char **)malloc(sizeof(char *) * (line_num + 2));
	if (!res)
	{
		return (NULL);
	}
	i = 0;
	while (i < line_num)
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
	return (res);
}

void	read_map_from_file(const char *file_path, t_game *game)
// gameポインタを受け取るように変更
{
	(void)file_path;


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

	int fd;
	int i;
	char *tmp_line;

	fd = open("./map/test.ber", O_RDONLY);
	game->map.data = NULL;
	i = 0;

	while (1)
	{
		tmp_line = get_next_line(fd);
		// ft_printf("	tmp_line:%s\n", tmp_line);

		game->map.data = ft_stradd(game->map.data, tmp_line);
		if (!tmp_line)
			break ;
		ft_printf("	each line of map.data : %s\n", game->map.data[i]);
		i++;
	}
	my_print_map(game->map.data);
	close(fd);

	game->map.width = ft_strlen(game->map.data[0]);
	game->map.height = i;

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
				mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, current_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	check_walls(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x++ < map->width - 1)
	{
		if (map->data[0][x] != '1' || map->data[map->height - 1][x] != '1')
		{
			ft_printf(" x = %d \n", x);
			error_exit("walls check error (top or bottom)");
		}
	}
	while (y++ < map->height - 1)
	{
		if (map->data[y][0] != '1' || map->data[y][map->width - 1] != '1')
		{
			error_exit("walls check error (both sides)");
		}
	}
	// ft_printf("walls check is OK. \n", x);
}

void	check_elements(t_map *map)
{
	int		x;
	int		y;
	char	c;

	x = 0;
	y = 0;
	map->player_count = 0;
	map->exit_count = 0;
	map->collectible_count = 0;
	while (y++ < map->height - 1)
	{
		while (x++ < map->width - 1)
		{
			c = map->data[y][x];
			if (c == 'P')
			{
				map->player_count++;
				map->player_pos_x = x;
				map->player_pos_y = y;
			}
			else if (c == 'E')
			{
				map->exit_count++;
			}
			else if (c == 'C')
			{
				map->collectible_count++;
			}
			else if (c != '0' && c != '1')
			{
				error_exit("Map contains invalid characters. (Allowed: 0, 1, P, E, C) ");
			}
			// ft_printf(" x:%d,y:%d \n", x, y);
		}
		x = 0;
	}
	if (map->player_count != 1)
	{
		ft_printf(" player_count : %d \n", map->player_count);
		error_exit("Map must contain exactly one player ('P').");
	}
	if (map->exit_count != 1)
	{
		error_exit("Map must contain exactly one exit ('E').");
	}
	if (map->collectible_count < 1)
	{
		error_exit("Map must contain at least one collectible ('C').");
	}
}

void	validate_map(t_map *map)
{
	ft_printf(" --- Validating map --- \n");
	check_walls(map);
	check_elements(map);
	// check_path_existence(map);
	printf(" --- Map validation successful ---\n");
}

// path check

// int is_queue_empty(t_queue *q)
// {
//     return (q->front == NULL);
// }

// t_queue	*create_queue(void)
// {
// 	t_queue	*q;

// 	q = (t_queue *)malloc(sizeof(t_queue));
// 	if(!q)
// 	{
// 		return (NULL);
// 	}
// 	q->front = NULL;
// 	q->rear = NULL;
// 	q->size = 0;
// 	return (q);
// }

// void	enqueue(t_queue *q, int x, int y)
// {
// 	t_queue_node	*new_node;

// 	new_node = (t_queue_node *)malloc(sizeof(t_queue_node));
// 	if (!new_node)
// 		return ;
// 	new_node->x = x;
// 	new_node->y = y;
// 	new_node->next = NULL;
// 	if (is_queue_empty(q))
// 	{
// 		q->rear->next = new_node;
// 		q->rear = new_node;
// 	}
// 	q->size++;
// }

// t_queue_node *dequeue(t_queue *q)
// {
// 	t_queue_node *temp;

// 	if(is_queue_empty(q))
// 		return (NULL);
// 	temp = q->front;
// 	q->front = q->front->next;
// 	if(q->front == NULL)
// 		q->rear = NULL;
// 		q->size--;
// 		return(temp);
// }



bool	is_valid_position_to_fill(char **grid, int width, int height, int x,
		int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return (false);
	if (grid[y][x] == WALL || grid[y][x] == VISITED)
		return (false);
	return (true);
}

void	my_flood_fill(char **grid, int width, int height, int x, int y)
{
	int	dx[] = {0, 0, -1, 1};
	int	dy[] = {-1, 1, 0, 0};

	if (!is_valid_position_to_fill(grid, width, height, x, y))
		return ;
	if (grid[y][x] == EXIT)
	{
		grid[y][x] = VISITED;
		ft_printf(" --- VISITED filled EXIT at [column:%d,line:%d] --- \n", x + 1, y + 1);
		return ;
	}
	grid[y][x] = VISITED;
	my_flood_fill(grid, width, height, x + dx[UP], y + dy[UP]);
	my_flood_fill(grid, width, height, x + dx[DOWN], y + dy[DOWN]);
	my_flood_fill(grid, width, height, x + dx[LEFT], y + dy[LEFT]);
	my_flood_fill(grid, width, height, x + dx[RIGHT], y + dy[RIGHT]);
}

bool	map_includes_specific_char(char **grid, int width, int height, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (grid[i][j] == c)
			{
				ft_printf(" --- found specified char at [column:%d,line:%d] --- \n", j + 1, i + 1);
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	validate_playability(t_game *game)
{
	char	**grid_copy;
	int		i;
	int		p_x;
	int		p_y;

	ft_printf(" --- Validating map path playability with Flood Fill (DFS) --- \n");
	grid_copy = (char **)malloc(sizeof(char *) * game->map.height);
	if (!grid_copy)
		error_exit("Memory allocation failed for flood fill map copy.");
	i = 0;
	while (i < game->map.height)
	{
		grid_copy[i] = ft_strdup(game->map.data[i]);
		if (!grid_copy[i])
		{
			free_double_ptr(grid_copy, i);
			error_exit("Memory allocation failed for flood fill row copy.");
		}
		i++;
	}
	p_x = game->map.player_pos_x;
	p_y = game->map.player_pos_y;
	my_flood_fill(grid_copy, game->map.width, game->map.height, p_x, p_y);
	ft_printf(" --- printing map after my_flood_fill ---\n");
	if (map_includes_specific_char(grid_copy, game->map.width, game->map.height,
			COLLECTIBLE))
	{
		free_double_ptr(grid_copy, game->map.height);
		error_exit("Map is not playable: Not all collectibles are reachable.");
	}
	if (map_includes_specific_char(grid_copy, game->map.width, game->map.height,
			EXIT))
	{
		my_print_map(grid_copy); // you must remove this line
		free_double_ptr(grid_copy, game->map.height);
		error_exit("Map is not playable: Exit is not reachable.");
	}
	ft_printf(" --- Map path playability validation successful. ---\n");
	free_double_ptr(grid_copy, game->map.height);
}

int	is_valid_move_position(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->data[y][x] == '1')
		return (0);
	return (1);
}

void handle_game_clear(t_game *game)
{
	ft_printf(" --- Congratulations! You cleared the game! --- ");
	ft_printf(" Total moves: %d\n", game->move_count);
	close_window_hook(game);
}

int move_player(t_game *game, int dx, int dy)
{
	int new_player_pos_x;
	int new_player_pos_y;
	char target_cell;

	new_player_pos_x = game->map.player_pos_x + dx;
	new_player_pos_y = game->map.player_pos_y + dy;

	if(!is_valid_move_position(&(game->map),new_player_pos_x, new_player_pos_y))
	{
		return (0);
	}
	target_cell = game->map.data[new_player_pos_y][new_player_pos_x];
	if(target_cell == EXIT)
	{
		if(game->map.collectible_count == 0)
		{
			game->move_count++;
			ft_printf("counts of moves: %d\n", game->move_count);
			handle_game_clear(game);
		}
		else
		{
			ft_printf("You need to collect all items before exiting!\n");
			return (0);
		}
	}
	game->map.data[game->map.player_pos_y][game->map.player_pos_x] = FLOOR;
	game->map.player_pos_x = new_player_pos_x;
	game->map.player_pos_x = new_player_pos_y;
	game->map.data[game->map.player_pos_y][game->map.player_pos_x] = PLAYER;

	if(target_cell == COLLECTIBLE)
	{
		game->map.collectible_count--;
		ft_printf("You've got an item! You need to get %d more items.\n", game->map.collectible_count);
	}
	game->move_count++;
	ft_printf("counts of moves: %d\n", game->move_count);
	render_map(game);
	return (1);
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
	game.img_wall = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/wall.xpm",
			&game.img_width, &game.img_height);
	if (!game.img_wall)
		error_exit("Failed to load wall image");
	game.img_floor = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/floor.xpm",
			&game.img_width, &game.img_height);
	if (!game.img_floor)
		error_exit("Failed to load floor image");
	game.img_player = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/player.xpm", &game.img_width, &game.img_height);
	if (!game.img_player)
		error_exit("Failed to load player image");
	game.img_collectible = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/collectible.xpm", &game.img_width, &game.img_height);
	if (!game.img_collectible)
		error_exit("Failed to load collectible image");
	game.img_exit = mlx_xpm_file_to_image(game.mlx_ptr, "./textures/exit.xpm",
			&game.img_width, &game.img_height);
	if (!game.img_exit)
		error_exit("Failed to load exit image");
	game.move_count = 0;
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	// draw_image(&game);
	read_map_from_file("", &game);
	validate_map(&(game.map));
	validate_playability(&game);
	render_map(&game);
	mlx_loop(game.mlx_ptr); // what's this function ?
	if (game.img_collectible)
	{
		mlx_destroy_image(game.mlx_ptr, game.img_collectible);
	}
	// destroy_game_resources(&game);
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
