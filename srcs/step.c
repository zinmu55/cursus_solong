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
}

void	update_counts(t_map *map, int x, int y)
{
	char	c;

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

void	count_elements(t_map *map)
{
	int		x;
	int		y;

	x = -1;
	y = -1;
	map->player_count = 0;
	map->exit_count = 0;
	map->collectible_count = 0;
	while (++y < map->height)
	{
		while (++x < map->width)
		{
			update_counts(map, x, y);
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

bool	is_valid_position_to_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	if (map->data[y][x] == WALL || map->data[y][x] == VISITED)
		return (false);
	return (true);
}

void	my_flood_fill(t_map *map, int x, int y)
{
	const int	dx[] = {0, 0, -1, 1};
	const int	dy[] = {-1, 1, 0, 0};

	if (!is_valid_position_to_fill(map, x, y))
		return ;
	if (map->data[y][x] == EXIT)
	{
		map->data[y][x] = VISITED;
		return ;
	}
	map->data[y][x] = VISITED;
	my_flood_fill(map, x + dx[UP], y + dy[UP]);
	my_flood_fill(map, x + dx[DOWN], y + dy[DOWN]);
	my_flood_fill(map, x + dx[LEFT], y + dy[LEFT]);
	my_flood_fill(map, x + dx[RIGHT], y + dy[RIGHT]);
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
				return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

char	**copy_map_data(t_map *map)
{
	char	**copy_grid;
	int i;

	copy_grid = (char **)malloc(sizeof(char *) * (map->height + 1));
	if (copy_grid)
		NULL;
	i = 0;
	while (i < map->height)
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
	t_map	copied_map;

	copied_map.data = copy_map_data(map);	// you should edit copy_map_data
	if (!copied_map.data)
		error_exit("Memory allocation failed map copy data in flood fill.");	//	you must free map & game ptr. 
	copied_map.width = map->width;
	copied_map.height = map->height;

	// you should use *map as argument
	my_flood_fill(&copied_map, map->player_pos_x, map->player_pos_y);
	if (map_includes_specific_char(copied_map.data, map->width, map->height, COLLECTIBLE))
	{
		free_double_ptr(copied_map.data, map->height);
		error_exit("Map is not playable: Not all collectibles are reachable.");
	}
	if (map_includes_specific_char(copied_map.data, map->width, map->height, EXIT))
	{
		free_double_ptr(copied_map.data, map->height);
		error_exit("Map is not playable: Exit is not reachable.");
	}
	ft_printf(" --- Map path playability validation successful. ---\n");
	free_double_ptr(copied_map.data, copied_map.height);
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
	ft_printf(" --- Congratulations! You cleared the game! --- \n");
	ft_printf(" Total moves: %d\n", game->move_count);
	close_window_hook(game);
}

int	move_to_exit(t_game *game)
{
	if(game->map.collectible_count == 0)
	{
		game->move_count++;
		ft_printf("counts of moves: %d\n", game->move_count);
		handle_game_clear(game);
		return (1);	// you must check neccesity below.
	}
	else
	{
		ft_printf("You need to collect all items before exiting!\n");
		return (0);
	}
}

void	moving_on_floor(t_game *game, int new_pos_x, int new_pos_y)
{
	game->map.data[game->map.player_pos_y][game->map.player_pos_x] = FLOOR;
	game->map.player_pos_x = new_pos_x;
	game->map.player_pos_y = new_pos_y;
	game->map.data[game->map.player_pos_y][game->map.player_pos_x] = PLAYER;
}

//	you can convert handle_collectible section to another function. 
int move_player(t_game *game, int dx, int dy)
{
	int new_player_pos_x;
	int new_player_pos_y;
	char target_cell;

	new_player_pos_x = game->map.player_pos_x + dx;
	new_player_pos_y = game->map.player_pos_y + dy;
	if(!is_accessible_position(&(game->map),new_player_pos_x, new_player_pos_y))
		return (0);
	target_cell = game->map.data[new_player_pos_y][new_player_pos_x];
	if(target_cell == EXIT)
	{
		if(!move_to_exit(game))
			return (0);
	}
	moving_on_floor(game, new_player_pos_x, new_player_pos_y);
	if(target_cell == COLLECTIBLE)
		ft_printf("You've got an item! You need to get %d more items.\n", game->map.collectible_count--);
	game->move_count++;
	ft_printf(" counts of moves : %d \n", game->move_count);
	render_map(game);
	return (1);
}

int	close_window_hook(t_game *game)
{
	ft_putendl_fd(" --- window close hook --- ", STDOUT_FILENO);
	if (game->mlx_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	exit(0);	//	check whether you can exit here (or return?). error_extt?
}

int	key_press_hook(int keycode, t_game *game)
{
	ft_putendl_fd(" --- key press hook --- ", STDOUT_FILENO);
	if (keycode == KEY_ESC)
	{
		ft_putendl_fd(" --- ESC key : window close hook --- ", STDOUT_FILENO);
		close_window_hook(game);
	}
	else if(keycode == KEY_W)
		move_player(game, 0, -1);
	else if(keycode == KEY_S)
		move_player(game, 0, 1);
	else if(keycode == KEY_A)
		move_player(game, -1, 0);
	else if(keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}

void	load_images(t_game *game)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/wall.xpm",
			&(game->img_width), &(game->img_height));
	if (!game->img_wall)
		error_exit("Failed to load wall image");
	game->img_floor = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/floor.xpm",
			&(game->img_width), &(game->img_height));
	if (!game->img_floor)
		error_exit("Failed to load floor image");
	game->img_player = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/player.xpm", &(game->img_width), &(game->img_height));
	if (!game->img_player)
		error_exit("Failed to load player image");
	game->img_collectible = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/collectible.xpm", &(game->img_width), &(game->img_height));
	if (!game->img_collectible)
		error_exit("Failed to load collectible image");
	game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/exit.xpm",
			&(game->img_width), &(game->img_height));
	if (!game->img_exit)
		error_exit("Failed to load exit image");
}

int	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (1);
	game->win_ptr = mlx_new_window(game->mlx_ptr, 1200, 800, "STEP window");
	if (game->win_ptr == NULL)
		return (1);
	ft_putendl_fd(" --- open a window --- ", STDOUT_FILENO);
	game->move_count = 0;
	return(0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_printf("use just 1 parameter (map file path) with this program. \n");
		return (1);
	}
	if (init_game(&game))
		return (1);
	load_images(&game);
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	read_map_from_file(argv[1], &game);
	validate_map(&(game.map));
	render_map(&game);
	mlx_loop(game.mlx_ptr);
	destroy_game_resources(&game);
	return (0);
}
