NAME := miniRT

CC := cc
CFLAGS := -Wall -Wextra -Werror
RM := rm -rf

LIBFT := ./libs/libft
LIBMLX := ./libs/MLX42

# Linux
LIBS := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
# Mac
# LIBS := $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -L/opt/homebrew/lib -ldl -lglfw -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit

HEADERS := includes/color.h \
	includes/constants.h \
	includes/hit_record.h \
	includes/libs.h \
	includes/mini_rt.h \
	includes/object.h \
	includes/ray.h \
	includes/vector3.h \
	includes/world_and_camera.h \

SRCS := \
	srcs/color/color_create.c \
	srcs/color/color_get.c \
	srcs/color/color_operation.c \
	\
	srcs/display/closing.c \
	srcs/display/init_display.c \
	srcs/display/modify_camera.c \
	\
	srcs/object/hit_cylinder.c \
	srcs/object/hit_plane.c \
	srcs/object/hit_sphere.c \
	srcs/object/add_object.c \
	\
	srcs/parser/parsing.c \
    srcs/parser/parsing_obj.c \
	srcs/parser/parsing_env.c \
	srcs/parser/parsing_util.c \
    srcs/parser/openfile.c \
    srcs/parser/error.c \
	srcs/parser/array.c \
	\
	srcs/renderer/configure_camera.c \
	srcs/renderer/is_ray_hit.c \
	srcs/renderer/ray_color.c \
	srcs/renderer/ray.c \
	srcs/renderer/render_image.c \
	srcs/renderer/hit_record.c \
	\
	srcs/vector3/vector3_create.c \
	srcs/vector3/vector3_add.c srcs/vector3/vector3_mul.c \
	srcs/vector3/vector3_dot.c srcs/vector3/vector3_dist.c \
	srcs/vector3/vector3_norm.c srcs/vector3/vector3_normalize.c \
	srcs/vector3/vector3_cross.c srcs/vector3/vector3_proj.c \
	\
	srcs/main.c

OBJS := $(SRCS:%.c=%.o)


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

.PHONY: all, clean, fclean, re, libft, libmlx
