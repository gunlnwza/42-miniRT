NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

HEADERS := mini_rt.h vector3.h color.h ray.h sphere.h world.h camera.h
SRCS := main.c vector3.c color.c ray.c sphere.c world.c camera.c
OBJS := $(SRCS:%.c=%.o)

LIBFT := ./libft
LIBMLX:= ./MLX42

LIBS := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm  # Linux
# LIBS := -framework Cocoa -framework OpenGL -framework IOKit  # Mac

.PHONY: all, clean, fclean, re, libft, libmlx

all: libft libmlx $(NAME)

libft: $(LIBFT)/libft.a

$(LIBFT)/libft.a:
	make -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) $(HEADERS)  # Linux
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
# $(NAME): $(OBJS) $(HEADERS)  # Mac
# 	$(CC) $(OBJS) $(LIBS) -framework Cocoa -framework OpenGL -framework IOKit -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT)
	$(RM) $(LIBMLX)/build
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(LIBFT)/libft.a
	$(RM) $(NAME)

re: fclean all
