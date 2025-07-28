#include "./solong.h"

void	error_exit(char *message)
{
	ft_putstr_fd(" --- error exit --- ", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	my_print_map(char **mapdata)	// you will comment out this function.
{
	int	y;

	ft_printf(" --- Current Map State --- \n");
	y = 0;
	while (mapdata[y])
	{
		ft_printf("	%s\n", mapdata[y]);
		y++;
	}
	ft_printf(" ------------------------- \n");
}

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

size_t	count_double_array_lines(char **double_array)
{
	size_t	line_num;

	line_num = 0;
	while(double_array && double_array[line_num])
	{
		line_num++;
	}
	return(line_num);
}

char	**ft_stradd(char **double_array, char *new_str)
{
	char	**res;
	size_t	i;
	size_t	line_num;

	line_num = count_double_array_lines(double_array);
	if (!new_str)
		return (double_array);
	res = (char **)malloc(sizeof(char *) * (line_num + 2));
	if (!res)
		return (NULL);
	i = 0;
	while (i < line_num)
	{
		res[i] = double_array[i];
		i++;
	}
	res[i++] = new_str;
	res[i] = NULL;
	free(double_array);
	return (res);
}

void	read_map_from_file(const char *file_path, t_game *game)
{
	(void)file_path;
	int fd;
	int i;
	char *tmp_line;
	file_path = "./map/test2.ber";	//	you need to remove this line & add function to get file_path.
	fd = open(file_path, O_RDONLY);
	game->map.data = NULL;
	i = 0;

	while (1)
	{
		tmp_line = get_next_line(fd);
		game->map.data = ft_stradd(game->map.data, tmp_line);
		if (!tmp_line)
			break ;
		i++;
	}
	my_print_map(game->map.data);
	close(fd);
	game->map.width = ft_strlen(game->map.data[0]);
	game->map.height = i;
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

void	count_elements(t_map *map)
{
	int		x;
	int		y;
	char	c;

	x = -1;
	y = -1;
	map->player_count = 0;
	map->exit_count = 0;
	map->collectible_count = 0;
	while (++y < map->height)
	{
		while (++x < map->width)
		{
			c = map->data[y][x];
			if (c == 'P')
			{
				map->player_count++;
				map->player_pos_x = x;
				map->player_pos_y = y;
			}
			else if (c == 'E')
				map->exit_count++;
			else if (c == 'C')
				map->collectible_count++;
			else if (c != '0' && c != '1')
				error_exit("Map contains invalid characters. (Allowed: 0, 1, P, E, C) ");
		}
		x = -1;
	}
}

void	check_elements(t_map *map)
{
	count_elements(map);
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

char	**map_copy(t_map *map)
{
	char	**copy_grid;
	int i;

	copy_grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if(copy_grid)
		NULL;
	i = 0;
	while(i < map->height)
	{
		copy_grid[i] = ft_strdup(map->data[i]);
		if (!copy_grid[i])
		{
			free_double_ptr(copy_grid, i);
			return NULL;
		}
		i++;
	}
	copy_grid[i] = NULL;
	return copy_grid;
}

void	validate_playability(t_map *map)
{
	char	**copy_grid;

	ft_printf(" --- Validating map path playability with Flood Fill (DFS) --- \n");	// you must comment out this line.
	copy_grid = map_copy(map);
	if (!copy_grid)
		error_exit("Memory allocation failed  flood fill map copy.");	//	you must free map & game ptr.
	my_flood_fill(copy_grid, map->width, map->height, map->player_pos_x, map->player_pos_y);
	ft_printf(" --- printing map after my_flood_fill ---\n");	// you must comment out this line.
	my_print_map(copy_grid);	// you must comment out this line.
	if (map_includes_specific_char(copy_grid, map->width, map->height, COLLECTIBLE))
	{
		free_double_ptr(copy_grid, map->height);
		error_exit("Map is not playable: Not all collectibles are reachable.");
	}
	if (map_includes_specific_char(copy_grid, map->width, map->height, EXIT))
	{
		my_print_map(copy_grid); // you must remove this line
		free_double_ptr(copy_grid, map->height);
		error_exit("Map is not playable: Exit is not reachable.");
	}
	ft_printf(" --- Map path playability validation successful. ---\n");
	free_double_ptr(copy_grid, map->height);
}

void	validate_map(t_map *map)
{
	ft_printf(" --- Validating map --- \n");
	check_walls(map);
	check_elements(map);
	validate_playability(map);
	printf(" --- Map validation successful ---\n");
}

int	is_accessible_position(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->data[y][x] == '1')
		return (0);
	return (1);
}

void	my_render_tile(t_game *game, int x, int y, char tile)
{
	void	*tile_img;

	tile_img = NULL;
	if (tile == '1')
		tile_img = game->img_wall;
	else if (tile == '0')
		tile_img = game->img_floor;
	else if (tile == 'P')
		tile_img = game->img_player;
	else if (tile == 'C')
		tile_img = game->img_collectible;
	else if (tile == 'E')
		tile_img = game->img_exit;
	if (tile_img)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, tile_img, x * TILE_SIZE, y * TILE_SIZE);
}

int	render_map(t_game *game)
{
	int		x;
	int		y;
	// void	*current_img;
	// char	cell;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			my_render_tile(game, x, y, game->map.data[y][x]);
			x++;
		}
		y++;
	}
	return (0);
}

void handle_game_clear(t_game *game)
{
	ft_printf(" --- Congratulations! You cleared the game! --- ");
	ft_printf(" Total moves: %d\n", game->move_count);
	close_window_hook(game);
}

//	--- now check here --- 

// int	move_to_exit(t_game *game)
// {
// 	if(game->map.collectible_count == 0)
// 		{
// 			game->move_count++;
// 			ft_printf("counts of moves: %d\n", game->move_count);
// 			handle_game_clear(game);
// 			return (1);	// you must check neccesariness below
// 		}
// 	else
// 	{
// 		ft_printf("You need to collect all items before exiting!\n");
// 		return (0);
// 	}
// }

int move_player(t_game *game, int dx, int dy)
{
	int new_player_pos_x;
	int new_player_pos_y;
	char target_cell;

	// new_player_pos_x = game->map.player_pos_x + dx;
	// new_player_pos_y = game->map.player_pos_y + dy;
	dx += game->map.player_pos_x;
	dy += game->map.player_pos_y;


	if(!is_accessible_position(&(game->map),dx, dy))
		return (0);
	target_cell = game->map.data[dx][dy];
	if(target_cell == EXIT)	//	you can convert this block to handle_exit function. 
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
	//	you can convert below to moving_floor function.
	game->map.data[game->map.player_pos_y][game->map.player_pos_x] = FLOOR;
	game->map.player_pos_x = dx;
	game->map.player_pos_y = dy;
	game->map.data[game->map.player_pos_y][game->map.player_pos_x] = PLAYER;

	//	you can convert the section below to handle_collectible function. 
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
		ft_printf(" --- W key was pressed. --- \n");	//	you should comment out this line.
		move_player(game, 0, -1);
	}
	else if(keycode == KEY_S)
	{
		ft_printf(" --- S key was pressed. --- \n");	//	you should comment out this line.
		move_player(game, 0, 1);
	}
	else if(keycode == KEY_A)
	{
		ft_printf(" --- A key was pressed. --- \n");	//	you should comment out this line.
		move_player(game, -1, 0);
	}
	else if(keycode == KEY_D)
	{
		ft_printf(" --- D key was pressed. --- \n");	//	you should comment out this line.
		move_player(game, 1, 0);
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
	game.win_ptr = mlx_new_window(game.mlx_ptr, 1200, 800, "STEP window");
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
	// validate_playability(&game);
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
