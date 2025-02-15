/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:42:01 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:08:28 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object.h"

t_object	*create_cylinder(const t_vector3 *point, double radius,
				const t_vector3 *normal, int color, double height)
{
	t_object	*cylinder;

	cylinder = malloc(sizeof(t_object));
	if (cylinder == NULL)
		return (NULL);
	cylinder->type = CYLINDER;
	cylinder->point = v_copy(point);
	cylinder->radius = radius;
	cylinder->normal = v_copy(normal);
	cylinder->color = color;
	cylinder->height = height;
	return (cylinder);
}

static void	save_to_record(t_hit_record *rec, double root,
				const t_ray *ray, t_object *cylinder, t_vector3 *A_p, t_vector3 *D_p)
{
	rec->t = root;
	ray_at(ray, rec->t, &rec->point);
	\
	rec->normal = v_copy(D_p);
	v_scalar_mul_ip(&rec->normal, rec->t);
	v_add_ip(&rec->normal, A_p);
	v_normalize_ip(&rec->normal);
	\
	rec->color = cylinder->color;
}

int	hit_cylinder(t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	t_vector3	A;
	t_vector3	A_p;
	t_vector3	D_p;
	double		a, b, c, discriminant, sqrtd, root;

	A = v_copy(&ray->origin);
	v_sub_ip(&A, &cylinder->point);
	A_p = v_rej(&A, &cylinder->normal);
	D_p = v_rej(&ray->direction, &cylinder->normal);

	a = v_norm2(&D_p);
	b = 2 * v_dot(&A_p, &D_p);
	c = v_norm2(&A_p) - cylinder->radius * cylinder->radius;

	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	
	sqrtd = sqrt(discriminant);
	root = (-b - sqrtd) / (2 * a);
	if (root < RAY_T_MIN)
	{
		root = (-b + sqrtd) / (2 * a);
		if (root < RAY_T_MIN)
			return (FALSE);
	}

	// insert logic for finite cylinder, and caps here

	save_to_record(rec, root, ray, cylinder, &A_p, &D_p);
	return (TRUE);
}
