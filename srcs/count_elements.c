/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:40:16 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/03 19:40:18 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./solong.h"

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
