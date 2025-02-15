/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:43:18 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 17:57:15 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object.h"

t_object	*create_plane(const t_vector3 *point, const t_vector3 *normal,
				int color)
{
	t_object	*plane;

	plane = malloc(sizeof(t_object));
	if (plane == NULL)
		return (NULL);
	plane->type = PLANE;
	plane->point = v_copy(point);
	plane->color = color;
	plane->normal = v_copy(normal);
	return (plane);
}

static void	save_to_record(t_hit_record *rec, double root,
				const t_ray *ray, t_object *plane)
{
	t_vector3	origin_to_point;

	rec->t = root;
	ray_at(ray, rec->t, &rec->point);
	\
	rec->normal = v_copy(&plane->normal);
	\
	origin_to_point = v_copy(&rec->point);
	v_sub_ip(&origin_to_point, &ray->origin);
	if (v_dot(&origin_to_point, &rec->normal) > 0)
		v_scalar_mul_ip(&rec->normal, -1);
	\
	rec->color = plane->color;
}

int	hit_plane(t_object *plane, const t_ray *ray, t_hit_record *rec)
{
	t_vector3	origin_to_point;
	double		root;

	origin_to_point = v_copy(&plane->point);
	v_sub_ip(&origin_to_point, &ray->origin);
	root = v_dot(&origin_to_point, &plane->normal) \
			/ v_dot(&ray->direction, &plane->normal);
	if (root <= RAY_T_MIN)
		return (0);
	save_to_record(rec, root, ray, plane);
	return (1);
}
