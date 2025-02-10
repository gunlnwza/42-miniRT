NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

HEADERS := includes/mini_rt.h includes/vector3.h includes/color.h includes/ray.h \
	includes/world.h includes/camera.h includes/utils.h \
	includes/constants.h includes/object.h

SRCS := \
	srcs/camera/configure_camera.c srcs/camera/is_ray_hit.c srcs/camera/ray_color.c srcs/camera/render_image.c  \
	\
	srcs/object/cylinder.c srcs/object/plane.c srcs/object/sphere.c \
	\
	srcs/main.c srcs/ray.c  srcs/world.c \
	\
	libs/vector3.c libs/color.c libs/utils.c

OBJS := $(SRCS:%.c=%.o)

LIBFT := ./libs/libft
LIBMLX:= ./libs/MLX42

LIBS := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm  # Linux
# LIBS := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/lib -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit  # Mac

.PHONY: all, clean, fclean, re, libft, libmlx

all: libft libmlx $(NAME)

libft: $(LIBFT)/libft.a

$(LIBFT)/libft.a:
	make -C $(LIBFT)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

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
