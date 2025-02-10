/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ray_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:49:37 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 13:53:48 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/camera.h"

int	is_ray_hit(const t_world *world, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	int				hit_anything;
	t_decimal		closest_so_far;
	int				i;
	int				ret;

	hit_anything = 0;
	closest_so_far = INF;
	i = 0;
	while (i < world->nb_objects)
	{

		if (world->objects[i]->type == SPHERE)
		{
			// printf("Sp ");
			ret = hit_sphere(world->objects[i], ray, &temp_rec);
		}
		else if (world->objects[i]->type == PLANE)
		{
			// printf("Pl ");
			ret = hit_plane(world->objects[i], ray, &temp_rec);
		}
		else
		{
			// printf("Cy ");
			ret = hit_cylinder(world->objects[i], ray, &temp_rec);
		}
		if (ret)
		{
			hit_anything = 1;
			if (temp_rec.t < closest_so_far)
			{
				closest_so_far = temp_rec.t;

				rec->normal = temp_rec.normal;
				rec->point = temp_rec.point;
				rec->t = temp_rec.t;
				rec->color = temp_rec.color;
			}
		}
		i++;
	}
	return (hit_anything);
}
