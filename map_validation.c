/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:41:50 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/03 20:29:30 by skohtake         ###   ########.fr       */
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

void	validate_playability(t_map *map)
{
	t_map	copied_map;

	copied_map.data = copy_map_data(map);
	if (!copied_map.data)
		error_exit("Memory allocation failed map copy data in flood fill.");
	copied_map.width = map->width;
	copied_map.height = map->height;
	my_flood_fill(&copied_map, map->player_pos_x, map->player_pos_y);
	if (map_includes_specific_char(copied_map.data, map->width, map->height,
			COLLECTIBLE))
	{
		free_double_ptr(copied_map.data, map->height);
		error_exit("Map is not playable: Not all collectibles are reachable.");
	}
	if (map_includes_specific_char(copied_map.data, map->width, map->height,
			EXIT))
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
