/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_and_hooks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:45:36 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/03 20:26:41 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

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
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
			tile_img, x * TILE_SIZE, y * TILE_SIZE);
}

int	render_map(t_game *game)
{
	int	x;
	int	y;

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

void	handle_game_clear(t_game *game)
{
	ft_printf(" --- Congratulations! You cleared the game! --- \n");
	ft_printf(" Total moves: %d\n", game->move_count);
	close_window_hook(game);
}

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
	if (keycode == KEY_ESC)
	{
		ft_putendl_fd(" --- ESC key : window close hook --- ", STDOUT_FILENO);
		close_window_hook(game);
	}
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}
