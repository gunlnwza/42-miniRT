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
				const t_ray *ray, t_object *cylinder)
{
	rec->t = root;
	rec->point = ray_at(ray, rec->t);
	\
	rec->normal = v_scalar_mul(&ray->direction, rec->t);
	v_add_ip(&rec->normal, &ray->origin);
	v_sub_ip(&rec->normal, &cylinder->point);
	v_normalize_ip(&rec->normal);
	\
	rec->color = cylinder->color;
}

static void	calculate_coef(t_object *cylinder, const t_ray *ray, double coef[3])
{
	t_vector3	A;
	t_vector3	A_perpen;
	t_vector3	D_perpen;

	A = v_sub(&ray->origin, &cylinder->point);
	A_perpen = v_rej(&A, &cylinder->normal);
	\
	D_perpen = v_rej(&ray->direction, &cylinder->normal);
	\
	coef[0] = v_norm2(&D_perpen);
	coef[1] = v_dot(&A_perpen, &D_perpen);
	coef[2] = v_norm2(&A_perpen) - cylinder->radius * cylinder->radius;
}

static int	hit_cylinder_cap_(t_object *cylinder, t_object *plane, const t_ray *ray, t_hit_record *rec)
{
	t_hit_record	plane_rec;

	if (hit_plane(plane, ray, &plane_rec))
	{
		if (v_dist(&plane_rec.point, &plane->point) < cylinder->radius)
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

static int	hit_cylinder_cap(t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	t_object	plane;
	t_vector3	height_vec;

	plane.color = cylinder->color;
	plane.normal = v_copy(&cylinder->normal);
	plane.point = v_copy(&cylinder->point);
	if (hit_cylinder_cap_(cylinder, &plane, ray, rec))
		return (TRUE);
	\
	height_vec = v_scalar_mul(&plane.normal, cylinder->height);
	v_add_ip(&plane.point, &height_vec);
	if (hit_cylinder_cap_(cylinder, &plane, ray, rec))
		return (TRUE);
	return (FALSE);
}

static int	have_root(double coef[3], double *root)
{
	double	discriminant;
	double	sqrtd;

	discriminant = coef[1] * coef[1] - coef[0] * coef[2];
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrt(discriminant);
	*root = (-coef[1] - sqrtd) / coef[0];
	if (*root < RAY_T_MIN)
	{
		*root = (-coef[1] + sqrtd) / coef[0];
		if (*root < RAY_T_MIN)
			return (FALSE);
	}
	return (TRUE);
}

int	hit_cylinder(t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	double		coef[3];
	double		root;
	t_vector3	intersection_point;
	t_vector3	base_to_point;
	double		height_pos;

	calculate_coef(cylinder, ray, coef);
	if (!have_root(coef, &root))
		return (FALSE);
	intersection_point = ray_at(ray, root);
	base_to_point = v_sub(&intersection_point, &cylinder->point);
	height_pos = v_dot(&base_to_point, &cylinder->normal);
	if (height_pos < 0 || height_pos > cylinder->height)
	{
		if (hit_cylinder_cap(cylinder, ray, rec))
			return (TRUE);
		return (FALSE);
	}
	save_to_record(rec, root, ray, cylinder);
	return (TRUE);
}
