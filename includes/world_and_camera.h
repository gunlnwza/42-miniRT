/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_and_camera.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:02 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 00:49:26 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_AND_CAMERA_H
# define WORLD_AND_CAMERA_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "object.h"
# include "color.h"

typedef struct s_camera
{
	t_vector3	center;
	int			deg_fov;
	t_vector3	normal;
	t_vector3	viewport_h;
	t_vector3	viewport_v;
	t_vector3	pixel_delta_h;
	t_vector3	pixel_delta_v;
	t_vector3	pixel00_loc;
}	t_camera;

typedef struct s_light
{
	int			color;
	t_vector3	point;
}	t_light;

typedef struct s_world
{
	t_object	*objects[100];
	int			nb_objects;
	int			ambient_light_color;
	t_camera	camera;
	t_light		light;
}	t_world;

void	configure_camera(t_camera *camera);

int		is_ray_hit(t_world *world, t_ray *ray, t_hit_record *rec);
int		ray_color(t_ray *ray, t_world *world);

#endif
