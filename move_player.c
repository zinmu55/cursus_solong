/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shintarokohtake <shintarokohtake@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:44:31 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/04 09:18:07 by shintarokoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

int	is_accessible_position(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (map->data[y][x] == '1')
		return (0);
	return (1);
}

int	move_to_exit(t_game *game)
{
	if (game->map.collectible_count == 0)
	{
		game->move_count++;
		ft_printf("counts of moves: %d\n", game->move_count);
		handle_game_clear(game);
		return (1);
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
int	move_player(t_game *game, int dx, int dy)
{
	int		new_player_pos_x;
	int		new_player_pos_y;
	char	target_cell;

	new_player_pos_x = game->map.player_pos_x + dx;
	new_player_pos_y = game->map.player_pos_y + dy;
	if (!is_accessible_position(&(game->map), new_player_pos_x,
			new_player_pos_y))
		return (0);
	target_cell = game->map.data[new_player_pos_y][new_player_pos_x];
	if (target_cell == EXIT)
	{
		if (!move_to_exit(game))
			return (0);
	}
	moving_on_floor(game, new_player_pos_x, new_player_pos_y);
	if (target_cell == COLLECTIBLE)
		ft_printf("You've got an item! You need to get %d more items.\n",
			--(game->map.collectible_count));
	game->move_count++;
	ft_printf(" counts of moves : %d \n", game->move_count);
	render_map(game);
	return (1);
}
