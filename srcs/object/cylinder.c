/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:42:01 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/25 14:02:09 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/object.h"

static void	calculate_coef(
	t_object *cylinder, const t_ray *ray, double coef[3])
{
	t_vector3	to_origin;
	t_vector3	to_origin_perpen;
	t_vector3	dir_perpen;

	to_origin = v_sub(&ray->origin, &cylinder->point);
	to_origin_perpen = v_rej(&to_origin, &cylinder->normal);
	\
	dir_perpen = v_rej(&ray->direction, &cylinder->normal);
	\
	coef[0] = v_norm2(&dir_perpen);
	coef[1] = v_dot(&to_origin_perpen, &dir_perpen);
	coef[2] = v_norm2(&to_origin_perpen) - cylinder->radius * cylinder->radius;
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

static int	hit_cylinder_cap(
	t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	double			r2;
	t_object		plane;
	t_hit_record	plane_rec;
	t_vector3		height_vec;

	rec->t = INF;
	r2 = cylinder->radius * cylinder->radius;
	plane.color = cylinder->color;
	plane.normal = v_copy(&cylinder->normal);  // base lid
	plane.point = v_copy(&cylinder->point);

	height_vec = v_scalar_mul(&plane.normal, cylinder->height);  // top lid
	v_add_ip(&plane.point, &height_vec);
	if (hit_plane(&plane, ray, &plane_rec)
		&& v_dist2(&plane_rec.point, &plane.point) < r2
		&& plane_rec.t < rec->t)
		hit_record_copy(rec, &plane_rec);

	v_sub_ip(&plane.point, &height_vec);

	if (hit_plane(&plane, ray, &plane_rec)
		&& v_dist2(&plane_rec.point, &plane.point) < r2)
		hit_record_copy(rec, &plane_rec);
	\
	
	return (rec->t < INF);
}

static void	save_to_record(t_hit_record *rec, double root,
				const t_ray *ray, t_object *cylinder)
{
	t_vector3	base_to_point;
	t_vector3	rej;

	rec->t = root;
	rec->point = ray_at(ray, rec->t);
	\
	base_to_point = v_sub(&rec->point, &cylinder->point);
	rej = v_rej(&base_to_point, &cylinder->normal);
	rec->normal = v_normalize(&rej);
	if (v_dot(&rec->normal, &ray->direction) > 0)
		v_scalar_mul_ip(&rec->normal, -1);
	\
	rec->color = cylinder->color;
}

int	hit_cylinder(t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	double		coef[3];
	double		root;
	t_vector3	intersection_point;
	t_vector3	base_to_point;
	double		height_pos;

	// this code is bad, I must take min_root of all: body, base lid, top lid
	calculate_coef(cylinder, ray, coef);
	if (!have_root(coef, &root))
		// return (FALSE);
		return (hit_cylinder_cap(cylinder, ray, rec));
	intersection_point = ray_at(ray, root);
	base_to_point = v_sub(&intersection_point, &cylinder->point);
	height_pos = v_dot(&base_to_point, &cylinder->normal);
	if (height_pos < 0 || height_pos > cylinder->height)
		// return (FALSE);
		return (hit_cylinder_cap(cylinder, ray, rec));
	save_to_record(rec, root, ray, cylinder);
	return (TRUE);
}
