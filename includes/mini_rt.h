#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "libs.h"
# include "world_and_camera.h"

// 解析器相关函数
int open_file(t_world *world, const char *filename);
int parse_params(t_world *world, char *line);
int parse_ambient(t_world *world, char *line);
int parse_camera(t_world *world, char *line);
int parse_light(t_world *world, char *line);
int parse_sphere(t_world *world, char **params);
int parse_plane(t_world *world, char **params);
int parse_cylinder(t_world *world, char **params);

// 工具函数
int parse_vector(char *str, t_vector3 *vect);
int parse_color(char *str, int *color);
int parse_double(char *str, double *num);

// 错误处理函数
int show_error(const char *msg);
int show_parsing_error(t_world *world, char **params, const char *msg);

void	free_array(char *arr[]);
int	    array_length(char *arr[]);

char    *sanitize_line(char *line);

#endif
