/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:15 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/22 09:23:12 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "libs.h"
# include "world_and_camera.h"

typedef struct s_flags
{
	int	parse_only;
}	t_flags;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_world		world;
	t_flags		flags;
}	t_data;

int		init_display(t_data *data);
void	render_image(mlx_image_t *img, t_world *world);

int		open_file(t_world *world, char *filename);
int		parse_params(t_world *world, char *line);
int		parse_ambient(t_world *world, char **params);
int		parse_camera(t_world *world, char **params);
int		parse_light(t_world *world, char **params);
int		parse_sphere(t_world *world, char **params);
int		parse_plane(t_world *world, char **params);
int		parse_cylinder(t_world *world, char **params);

int		is_valid_number(const char *str);
int		is_valid_double(const char *str);
int		parse_vector(char *str, t_vector3 *vect);
int		parse_color(char *str, int *color);
int		parse_double(char *str, double *num);

int		show_error(const char *msg);
int		show_parsing_error(t_world *world, char **params, const char *msg);

void	free_array(char *arr[]);
int		array_length(char *arr[]);

char	*sanitize_line(char *line);

int		ft_sscanf(const char *str, int *r, int *g, int *b);

void    free_data(t_data *data);

int		is_modify_camera_key(keys_t key);
void	modify_camera(t_camera *camera, keys_t key);

#endif
