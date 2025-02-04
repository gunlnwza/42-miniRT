NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM= rm -rf

HEADERS = mini_rt.h vector3.h
SRCS = main.c vector3.c
OBJS = $(SRCS:%.c=%.o)

LIBFT = libft/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lm -o $(NAME)

$(LIBFT):
	make -C libft

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all
