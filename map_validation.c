/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:41:50 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/08 20:40:04 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

bool	is_valid_position_to_fill(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	if (map->data[y][x] == WALL || map->data[y][x] == VISITED)
		return (false);
	return (true);
}

void	flood_fill(t_map *map, int x, int y)
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
	flood_fill(map, x + dx[UP], y + dy[UP]);
	flood_fill(map, x + dx[DOWN], y + dy[DOWN]);
	flood_fill(map, x + dx[LEFT], y + dy[LEFT]);
	flood_fill(map, x + dx[RIGHT], y + dy[RIGHT]);
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

void	validate_playability(t_game *game, t_map *map)
{
	t_map	copied_map;

	copied_map.data = copy_map_data(map);
	if (!copied_map.data)
		my_clean_error_exit(game, "Memory allocation failed map copy.");
	copied_map.width = map->width;
	copied_map.height = map->height;
	flood_fill(&copied_map, map->player_pos_x, map->player_pos_y);
	if (map_includes_specific_char(copied_map.data, map->width, map->height,
			COLLECTIBLE))
	{
		free_double_ptr(copied_map.data, map->height);
		my_clean_error_exit(game, "Not all collectibles are reachable.");
	}
	if (map_includes_specific_char(copied_map.data, map->width, map->height,
			EXIT))
	{
		free_double_ptr(copied_map.data, map->height);
		my_clean_error_exit(game, "Exit is not reachable.");
	}
	ft_printf(" --- Map path playability validation successful. ---\n");
	free_double_ptr(copied_map.data, copied_map.height);
}

void	validate_map(t_game *game)
{
	ft_printf(" --- Validating map --- \n");
	check_walls(game);
	check_elements(game);
	validate_playability(game, &(game->map));
	ft_printf(" --- Map validation successful ---\n");
}
