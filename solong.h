/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shintarokohtake <shintarokohtake@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:23:07 by skohtake          #+#    #+#             */
/*   Updated: 2025/08/04 08:52:58 by shintarokoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include "./ft_printf/includes/ft_printf.h"
# include "./gnl/get_next_line.h"
# include "./libft/includes/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# if defined(__linux__)
#  include "../mlx/minilibx_linux/mlx.h"
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100

# elif defined(__APPLE__)
#  include "../mlx/minilibx_opengl_20191021/mlx.h"
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2

# endif

# define TILE_SIZE 32
# define WALL '1'
# define FLOOR '0'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define VISITED 'V'
# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

typedef struct s_map
{
	char	**data;
	int		width;
	int		height;
	int		player_count;
	int		exit_count;
	int		collectible_count;
	int		player_pos_x;
	int		player_pos_y;
}			t_map;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_map	map;
	int		move_count;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_collectible;
	void	*img_exit;
	int		img_width;
	int		img_height;
}			t_game;

// Function Prototypes

// map_utils.c (or similar grouping)
void		my_print_map(char **mapdata);
size_t		count_double_array_lines(char **double_array);
char		**ft_stradd(char **double_array, char *new_str);
void		read_map_from_file(const char *file_path, t_game *game);
char		**copy_map_data(t_map *map);

// count_elements.c (or similar grouping)
void		check_walls(t_map *map);
void		update_counts(t_map *map, int x, int y);
void		count_elements(t_map *map);
void		check_elements(t_map *map);

// map_validation.c
bool		is_valid_position_to_fill(t_map *map, int x, int y);
void		my_flood_fill(t_map *map, int x, int y);
bool		map_includes_specific_char(char **grid, int width, int height,
				char c);
void		validate_playability(t_map *map);
void		validate_map(t_map *map);

// game_loop_and_hooks.c (or similar grouping)
int			close_window_hook(t_game *game);
int			key_press_hook(int keycode, t_game *game);
void		my_render_tile(t_game *game, int x, int y, char tile);
int			render_map(t_game *game);
void		handle_game_clear(t_game *game);

// move_player.c
int			is_accessible_position(t_map *map, int x, int y);
int			move_to_exit(t_game *game);
void		moving_on_floor(t_game *game, int new_pos_x, int new_pos_y);
int			move_player(t_game *game, int dx, int dy);

// error_exit.c (or similar grouping)
void		error_exit(char *message);
// resource_management.c (or similar grouping)
void		free_double_ptr(char **ptr, size_t count);
void		free_map_data(t_map *map);
void		destroy_game_resources(t_game *game);
void		load_images(t_game *game);

// initialization.c (or similar grouping)
// main.c
int			init_game(t_game *game);
int			main(int argc, char **argv);

#endif
