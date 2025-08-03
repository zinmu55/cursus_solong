# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skohtake <skohtake@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/19 20:52:26 by skohtake          #+#    #+#              #
#    Updated: 2025/08/03 18:01:16 by skohtake         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := step
SRCS := step.c

MLX_LIB := mlx

UNAME_S := $(shell uname)

ifeq ($(UNAME_S), Darwin) 
	MLX_DIR := ../minilibx_opengl_20191021
	LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB)  -framework OpenGL -framework AppKit -framework Cocoa
else ifeq ($(UNAME_S), Linux)
	MLX_DIR := ../minilibx_linux
    LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB) -lXext -lX11
else
	$(shell echo "Unsupported OS: " && echo $(UNAME_S))
endif

CC := cc
CFLAGS :=	-Wall -Wextra -Werror

all : $(NAME)

step : step.c
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS) -L../libft -lft -L../gnl -lgnl -L../ft_printf -lftprintf

linker :
	make -C ../libft re
	make -C ../gnl re
	make -C ../ft_printf re
	make -C ../libft clean
	make -C ../gnl clean
	make -C ../ft_printf clean

clean :
	rm -f *.o

fclean :
	make clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
