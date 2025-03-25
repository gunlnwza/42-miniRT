/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:48:54 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:39:43 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <fcntl.h>

# include "../libs/libft/libft.h"
# include "world_and_camera.h"

typedef enum e_scene_type
{
	SCENE_AMBIENT,
	SCENE_CAMERA,
	SCENE_LIGHT,
	SCENE_SPHERE,
	SCENE_PLANE,
	SCENE_CYLINDER,
	SCENE_INVALID
}	t_scene_type;

int				read_file_to_world(char *filename, t_world *world);

char			**load_file_into_memory(int fd);

t_scene_type	identify_scene_type(char *id);
int				validate_scene(int number_of_lines, char ***tokens);
int				parse_scene(int number_of_lines, char ***tokens,
					t_world *world);

void			free_array(char **arr);
int				array_length(char **arr);

double			parse_ratio(char *ratio_str);
int				parse_color(char *rgb_str, int *color);
int				parse_vector(char *xyz_str, t_vector3 *dest);
int				parse_normal_vector(char *normal_str, t_vector3 *dest);
int				parse_fov(char *fov_str);

int				validate_ambient(char **line);
int				parse_ambient(char **line, t_world *world);

int				validate_camera(char **line);
int				parse_camera(char **line, t_world *world);

int				validate_light(char **line);
int				parse_light(char **line, t_world *world);

int				validate_sphere(char **line);
int				parse_sphere(char **line, t_world *world);

int				validate_plane(char **line);
int				parse_plane(char **line, t_world *world);

int				validate_cylinder(char **line);
int				parse_cylinder(char **line, t_world *world);

int				is_in_range(int min, int max, int x);
int				is_in_rangef(double min, double max, double x);
int				is_same_after_ft_atoi(const char *nptr);
int				is_valid_ratio(char *ratio);
int				is_valid_color(char *rgb_str);
int				is_valid_pos(char *pos_str);
int				is_valid_normal(char *normal_str);
int				is_valid_length(char *length_str);
int				is_valid_fov(char *fov_str);

#endif
