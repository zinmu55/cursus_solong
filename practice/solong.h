#ifndef SOLONG_H
# define SOLONG_H

typedef struct s_queue_node
{
	int	x;
	int	y;
	struct s_queue_node	*next;
}	t_queue_node;

typedef struct s_queue
{
	t_queue_node	*front;
	t_queue_node	*rear;
	int	size;
}	t_queue;

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h> 
# include <stdbool.h>
# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/includes/libft.h"
# include "../gnl/get_next_line.h"
# include "../ft_printf/includes/ft_printf.h"

// # include "../minilibx-linux/mlx.h"

#endif