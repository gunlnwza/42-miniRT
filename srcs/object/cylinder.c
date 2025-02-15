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

#include <unistd.h>
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
				const t_ray *ray, t_object *cylinder, t_vector3 *A_perpen, t_vector3 *D_perpen)
{
	rec->t = root;
	rec->point = ray_at(ray, rec->t);
	\
	rec->normal = v_copy(D_perpen);
	v_scalar_mul_ip(&rec->normal, rec->t);
	v_add_ip(&rec->normal, A_perpen);
	v_normalize_ip(&rec->normal);
	\
	rec->color = cylinder->color;
}

int	hit_cylinder(t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	t_vector3	A;
	t_vector3	A_perpen;
	t_vector3	D;
	t_vector3	D_perpen;
	double		coef[3];
	double		discriminant, sqrtd;
	double		root;

	A = v_copy(&ray->origin);
	v_sub_ip(&A, &cylinder->point);
	A_perpen = v_rej(&A, &cylinder->normal);

	D = v_copy(&ray->direction);
	D_perpen = v_rej(&D, &cylinder->normal);

	coef[0] = v_norm2(&D_perpen);
	coef[1] = v_dot(&A_perpen, &D_perpen);
	coef[2] = v_norm2(&A_perpen) - cylinder->radius * cylinder->radius;

	discriminant = coef[1] * coef[1] - coef[0] * coef[2];
	if (discriminant < 0)
		return (FALSE);
	
	sqrtd = sqrt(discriminant);
	root = (-coef[1] - sqrtd) / coef[0];
	if (root < RAY_T_MIN)
	{
		root = (-coef[1] + sqrtd) / coef[0];
		if (root < RAY_T_MIN)
			return (FALSE);
	}

	t_vector3	intersection_point;
	intersection_point = ray_at(ray, root);

	t_vector3	base_to_point;
	base_to_point = v_sub(&intersection_point, &cylinder->point);

	double height_pos = v_dot(&base_to_point, &cylinder->normal);
	if (height_pos < 0 || height_pos > cylinder->height)
	{
		t_object	plane;
		t_hit_record plane_rec;

		plane.color = cylinder->color;
		plane.normal = v_copy(&cylinder->normal);
		plane.point = v_copy(&cylinder->point);

		// bottom cap
		if (hit_plane(&plane, ray, &plane_rec))
		{
			if (v_dist(&plane_rec.point, &plane.point) < cylinder->radius)
			{
				rec->color = plane_rec.color;
				rec->normal = plane_rec.normal;
				rec->point = plane_rec.point;
				rec->t = plane_rec.t;
				return (TRUE);
			}
		}

		// top cap
		t_vector3	height_vec;
		height_vec = v_copy(&plane.normal);
		v_scalar_mul_ip(&height_vec, cylinder->height);
		v_add_ip(&plane.point, &height_vec);

		if (hit_plane(&plane, ray, &plane_rec))
		{
			if (v_dist(&plane_rec.point, &plane.point) < cylinder->radius)
			{
				rec->color = plane_rec.color;
				rec->normal = plane_rec.normal;
				rec->point = plane_rec.point;
				rec->t = plane_rec.t;
				return (TRUE);
			}
		}
		return (FALSE);
	}
	save_to_record(rec, root, ray, cylinder, &A_perpen, &D_perpen);
	return (TRUE);
}
