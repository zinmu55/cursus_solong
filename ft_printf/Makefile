# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shintarokohtake <shintarokohtake@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 11:04:36 by yonuma            #+#    #+#              #
#    Updated: 2025/07/30 20:17:43 by shintarokoh      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FILES = ft_printf.c \
		my_print_func.c \
		my_print_hex.c \
		my_print_ptr.c 

SRCS = $(addprefix srcs/, $(FILES))

OBJS = $(SRCS:.c=.o)

RM = rm -f

CC = cc -c

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes

AR = ar rc

LIBFT = libft/libft.a

$(NAME) : $(OBJS)
	make -C libft
	cp $(LIBFT) $(NAME)
	$(AR) $@ $^

all : $(NAME)

%.o:%.c
	cp libft/includes/libft.h includes/
	$(CC) $(CFLAGS) $^ -o $@ $(INCLUDES)

clean : 
	make -C libft clean
	$(RM) $(OBJS)

fclean :
	make -C libft fclean
	make clean
	$(RM) $(NAME) includes/libft.h

re : fclean all

.PHONY : all clean fclean re
