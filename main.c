/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:47:53 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/08 21:00:54 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

int	init_game(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (game->mlx_ptr == NULL)
		return (1);
	game->win_ptr = NULL;
	game->map.data = NULL;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_player = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
	game->move_count = 0;
	return (0);
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
	read_map_from_file(argv[1], &game);
	validate_map(&game);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map.width * TILE_SIZE,
			game.map.height * TILE_SIZE, "So Long window");
	if (game.win_ptr == NULL)
		return (1);
	mlx_hook(game.win_ptr, 17, 1L << 17, close_window_hook, &game);
	mlx_hook(game.win_ptr, 2, 1L << 0, key_press_hook, &game);
	load_images(&game);
	render_map(&game);
	mlx_loop(game.mlx_ptr);
	destroy_game_resources(&game);
	return (0);
}
