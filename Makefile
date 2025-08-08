# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/19 20:52:26 by skohtake          #+#    #+#              #
#    Updated: 2025/08/08 20:56:12 by skohtake         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := so_long
SRCS := map_utils.c count_elements.c map_validation.c game_loop_and_hooks.c move_player.c  resource_management.c main.c tmp.c
# SRCS := map_utils.c count_elements.c map_validation.c game_loop_and_hooks.c move_player.c  resource_management.c main.c
OBJS = $(SRCS:.c=.o)
UNAME_S := $(shell uname)
MLX_LIB := mlx

ifeq ($(UNAME_S), Darwin) 
	MLX_DIR := ./mlx/minilibx_opengl_20191021
	LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB)  -framework OpenGL -framework AppKit -framework Cocoa
else ifeq ($(UNAME_S), Linux)
	MLX_DIR := /home/skohtake/workspace/mlx/minilibx_linux
    LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB) -lXext -lX11
else
	$(shell echo "Unsupported OS: " && echo $(UNAME_S))
endif

CC := cc
CFLAGS := -Wall -Wextra -Werror
INCLUDES := -L./libft -lft -L./gnl -lgnl -L./ft_printf -lftprintf

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS) $(INCLUDES) 

%.o : %.c
	$(CC) -c $(CFLAGS) $^ -o $@
# 	$(CC) -c $(CFLAGS) $^ -o $@ $(INCLUDES) 

clean :
	rm -f *.o

fclean :
	make clean
	rm -f $(NAME)

re : fclean all

linker :
	make -C ./gnl re
	make -C ./gnl clean
	make -C ./ft_printf re
	make -C ./ft_printf clean
	make -C ./libft re
	make -C ./libft clean

.PHONY : all clean fclean re
