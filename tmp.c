
#include "./solong.h"

void	my_clean_game(t_game *game)
{
	// my_free_double_ptr(game->map.data);
	destroy_game_resources(game);
	// mlx_destroy_display(game->win_ptr);
	// free(game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	// mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game->mlx_ptr);
	// mlx_destroy(game->mlx_ptr);
	// free(game->mlx_ptr);
	// free(game->win_ptr);
}

void	my_clean_game_exit(t_game *game, char *message)
{
	my_clean_game(game);
	ft_putendl_fd(" --- error exit --- ", STDOUT_FILENO);
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
