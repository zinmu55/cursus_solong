# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skohtake <skohtake@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/18 11:04:36 by yonuma            #+#    #+#              #
#    Updated: 2024/05/24 13:35:12 by skohtake         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FILES = ft_isascii.c \
	   ft_isprint.c \
	   ft_isalnum.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_strlen.c \
	   ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_toupper.c\
	   ft_tolower.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strncmp.c \
	   ft_atoi.c \
	   ft_strnstr.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c

SRCS = $(addprefix srcs/, $(FILES))

OBJS = $(SRCS:.c=.o)

RM = rm -f

CC = cc -c

CFRAGS = -Wall -Wextra -Werror

INCLUDES = -I includes

AR = ar rc

$(NAME) : $(OBJS)
	$(AR) $@ $^
	ranlib $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@

all : $(NAME)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re