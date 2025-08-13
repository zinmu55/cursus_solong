/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 19:37:03 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/13 13:31:16 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

// void	error_exit(char *message)
// {
// 	ft_putstr_fd(" --- error exit --- ", STDOUT_FILENO);
// 	ft_putendl_fd(message, STDOUT_FILENO);
// 	exit(EXIT_FAILURE);
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

void	free_map_data(t_map *map)
{
	if (map->data)
	{
		free_double_ptr(map->data, map->height);
		map->data = NULL;
	}
}

void	destroy_game_resources(t_game *game)
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

void	load_images(t_game *game)
{
	game->img_wall = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/wall.xpm",
			&(game->img_width), &(game->img_height));
	if (!game->img_wall)
		my_clean_error_exit(game, "Failed to load wall image");
	game->img_floor = mlx_xpm_file_to_image(game->mlx_ptr,
			"./textures/floor.xpm", &(game->img_width), &(game->img_height));
	if (!game->img_floor)
		my_clean_error_exit(game, "Failed to load floor image");
	game->img_player = mlx_xpm_file_to_image(game->mlx_ptr,
			"./textures/player.xpm", &(game->img_width), &(game->img_height));
	if (!game->img_player)
		my_clean_error_exit(game, "Failed to load player image");
	game->img_collectible = mlx_xpm_file_to_image(game->mlx_ptr,
			"./textures/collectible.xpm", &(game->img_width),
			&(game->img_height));
	if (!game->img_collectible)
		my_clean_error_exit(game, "Failed to load collectible image");
	game->img_exit = mlx_xpm_file_to_image(game->mlx_ptr, "./textures/exit.xpm",
			&(game->img_width), &(game->img_height));
	if (!game->img_exit)
		my_clean_error_exit(game, "Failed to load exit image");
}
