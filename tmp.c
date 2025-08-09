/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:26:33 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/09 14:44:57 by skohtake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./solong.h"

void	my_clean_game(t_game *game)
{
	destroy_game_resources(game);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
}

void	my_clean_error_exit(t_game *game, char *message)
{
	my_clean_game(game);
	ft_putendl_fd("Error", STDOUT_FILENO);
	ft_putendl_fd(message, STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	my_free_double_ptr(char **ptr)
{
	size_t	i;

	i = 0;
	if (!ptr || !*ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
