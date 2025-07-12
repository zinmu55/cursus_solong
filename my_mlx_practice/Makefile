
NAME := step1 step2 test1 test2
SRCS := step1.c
MLX_DIR := ../minilibx-linux
MLX_LIB := mlx

# Linux (X11) 用のコンパイル・リンクフラグ
LFLAGS := -L$(MLX_DIR) -l$(MLX_LIB) -lXext -lX11
CC := cc
CFLAGS :=	# -Wall -Wextra -Werror

all : $(NAME)

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
