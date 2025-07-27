/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shintarokohtake <shintarokohtake@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:23:07 by skohtake          #+#    #+#             */
/*   Updated: 2025/07/27 12:39:24 by shintarokoh      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include "../ft_printf/includes/ft_printf.h"
# include "../gnl/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// # include "../minilibx-linux/mlx.h"

typedef struct s_map
{
	char				**data;
	int					width;
	int					height;
	int					player_count;
	int					exit_count;
	int					collectible_count;
	int					player_pos_x;
	int					player_pos_y;
}						t_map;

// typedef	struct s_img
// {
// 	void	*wall_img;
// 	void	*floor_img;
// 	void	*player_img;
// 	void	*collectible_img;
// 	void	*exit_img;
// 	int		width;
// 	int		height;
// }	t_img;

typedef struct s_game
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_map				map;
	int					move_count;
	// t_img	img;
	void				*img_wall;
	void				*img_floor;
	void				*img_player;
	void				*img_collectible;
	void				*img_exit;
	int					img_width;
	int					img_height;
}						t_game;

// typedef struct s_queue_node
// {
// 	int					x;
// 	int					y;
// 	struct s_queue_node	*next;
// }						t_queue_node;

// typedef struct s_queue
// {
// 	t_queue_node		*front;
// 	t_queue_node		*rear;
// 	int					size;
// }						t_queue;

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

# if defined(__linux__)
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100

# elif defined(__APPLE__)
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2

# endif

void					error_exit(char *message);
void					read_map_from_file(const char *file_path, t_game *game);
char					**ft_stradd(char **double_array, char *new_str);
void					free_double_ptr(char **ptr, size_t count);

void					check_walls(t_map *map);
void					check_elements(t_map *map);
void					validate_map(t_map *map);

// flood_fill_validation.c
void					my_flood_fill(char **grid, int width, int height, int x,
							int y);
bool					is_valid_position_to_fill(char **grid, int width,
							int height, int x, int y);
bool					map_includes_specific_char(char **grid, int width,
							int height, char c);
// void					validate_playability(t_game *game);
void					validate_playability(t_map *map);


// player_moves.c
int						is_valid_move_position(t_map *map, int x, int y);
void					handle_game_clear(t_game *game);
int						move_player(t_game *game, int dx, int dy);

// hooks.c (または main.c)
int						close_window_hook(t_game *game);
int						key_press_hook(int keycode, t_game *game);

// render.c
int						render_map(t_game *game);
int						draw_stuff(t_game *game);
int						draw_image(t_game *game);

// utility.c (または general utilities)
void					my_print_map(char **mapdata);
void					free_map_data(t_map *map);
void					destroy_game_resources(t_game *game);

// // movement keycode for Linux (X11)
// # define KEY_ESC 65307
// # define KEY_W 119
// # define KEY_A 97
// # define KEY_S 115
// # define KEY_D 100

// // movement keycode for macOS
// # define KEY_ESC_MAC 53
// # define KEY_W_MAC 13
// # define KEY_A_MAC 0
// # define KEY_S_MAC 1
// # define KEY_D_MAC 2

#endif
