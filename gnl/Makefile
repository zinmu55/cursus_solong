NAME = libgnl.a

FILES = get_next_line.c \
		get_next_line_utils.c

SRCS = $(FILES)

OBJS = $(SRCS:.c=.o)

RM = rm -f

CC = cc

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $@ $^

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@ $(INCLUDES)

clean : 
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re

# program below needs removing to submit