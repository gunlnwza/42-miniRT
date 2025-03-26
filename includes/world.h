/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:02 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 17:50:44 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../libs/libft/libft.h"
# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "object.h"
# include "color.h"
# include "camera.h"

# define MAX_OBJECTS 100

typedef struct s_light
{
	int			color;
	t_vector3	point;
}	t_light;

typedef struct s_world
{
	t_object	*objects[MAX_OBJECTS];
	int			nb_objects;
	int			ambient_light_color;
	t_camera	camera;
	t_light		light;
}	t_world;

int		is_ray_hit(t_world *world, t_ray *ray, t_hit_record *rec);
int		ray_color(t_ray *ray, t_world *world);

#endif
