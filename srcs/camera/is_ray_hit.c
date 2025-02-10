/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ray_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:37 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:07:53 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world_and_camera.h"

static int	is_hit_object(t_object *object, t_ray *ray, t_hit_record *temp_rec)
{
	if (object->type == SPHERE)
		return (hit_sphere(object, ray, temp_rec));
	else if (object->type == PLANE)
		return (hit_plane(object, ray, temp_rec));
	else
		return (hit_cylinder(object, ray, temp_rec));
}

static void	update_record(t_hit_record *rec, t_hit_record *temp_rec)
{
	rec->normal = temp_rec->normal;
	rec->point = temp_rec->point;
	rec->t = temp_rec->t;
	rec->color = temp_rec->color;
}

int	is_ray_hit(t_world *world, t_ray *ray, t_hit_record *rec)
{
	int				hit_anything;
	double			closest_so_far;
	int				i;
	t_hit_record	temp_rec;

	hit_anything = 0;
	closest_so_far = INF;
	i = 0;
	while (i < world->nb_objects)
	{
		if (is_hit_object(world->objects[i], ray, &temp_rec))
		{
			hit_anything = 1;
			if (temp_rec.t < closest_so_far)
			{
				closest_so_far = temp_rec.t;
				update_record(rec, &temp_rec);
			}
		}
		i++;
	}
	return (hit_anything);
}
