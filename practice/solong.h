/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:23:07 by skohtake          #+#    #+#             */
/*   Updated: 2025/07/26 20:32:07 by skohtake         ###   ########.fr       */
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

typedef struct s_queue_node
{
	int					x;
	int					y;
	struct s_queue_node	*next;
}						t_queue_node;

typedef struct s_queue
{
	t_queue_node		*front;
	t_queue_node		*rear;
	int					size;
}						t_queue;

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
