# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shintarokohtake <shintarokohtake@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/19 20:52:26 by skohtake          #+#    #+#              #
#    Updated: 2025/07/19 21:46:19 by shintarokoh      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME := step step1 step2 test1 test2
SRCS := step1.c

MLX_LIB := mlx

# # flag for LINUX
# MLX_DIR := ../minilibx_linux
# flag for Mac
MLX_DIR := ../minilibx_opengl_20191021

# # compilation flag for Linux(X11)
# LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB) -lXext -lX11
# # compilation flag for Mac
# LFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -framework Cocoa 

UNAME_S := $(shell uname)

# ifeq ($(UNAME_S), Darwin) 
# 	MLX_DIR := ../minilibx_linux
# else ifeq ($(UNAME_S), Linux)
# 	MLX_DIR := ../minilibx_opengl_20191021
# # else
# # 	$(shell echo "Unsupported OS: " && echo $(UNAME_S))
# endif

ifeq ($(UNAME_S), Darwin) 
	LFLAGS := -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -framework Cocoa
else ifeq ($(UNAME_S), Linux)
    LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB) -lXext -lX11
# else
# 	$(shell echo "Unsupported OS: " && echo $(UNAME_S))
endif

CC := cc
CFLAGS :=	# -Wall -Wextra -Werror

all : $(NAME)

step : step.c
	make -C ../libft
	make -C ../libft clean
	$(CC) -o $@ $(CFLAGS) $^ $(LFLAGS) -L../libft -lft

step1 : step1.c
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@
#	cc step1.c -L../minilibx-linux -lmlx -lXext -lX11 -o step1

step2 : step2.c
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

test1 : test1.c
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

test2 : test2.c
	$(CC) $(CFLAGS) $^ $(LFLAGS) -o $@

clean :
	rm -f *.o

fclean :
	make clean
	rm -f $(NAME)

re :
	make fclean
	all

.PHONY : all clean fclean re
