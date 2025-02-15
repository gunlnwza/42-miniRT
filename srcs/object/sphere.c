/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:57:43 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 17:58:07 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/object.h"
#include <stdio.h>

t_object	*create_sphere(const t_vector3 *center, double radius, int color)
{
	t_object	*sphere;

	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE;
	sphere->point = v_copy(center);
	sphere->color = color;
	sphere->radius = radius;
	return (sphere);
}

static void	calculate_coef(t_object *sphere, const t_ray *ray, double coef[3])
{
	t_vector3	oc;

	oc = v_copy(&sphere->point);
	v_sub_ip(&oc, &ray->origin);
	\
	coef[0] = v_norm2(&ray->direction);
	coef[1] = v_dot(&ray->direction, &oc);
	coef[2] = v_norm2(&oc) - (sphere->radius * sphere->radius);
}

static int	have_root(double coef[3], double *root)
{
	double	discriminant;
	double	sqrtd;

	discriminant = coef[1] * coef[1] - coef[0] * coef[2];
	if (discriminant < 0)
		return (FALSE);
	sqrtd = sqrtf(discriminant);
	*root = (coef[1] - sqrtd) / coef[0];
	if (*root < RAY_T_MIN)
	{
		*root = (coef[1] + sqrtd) / coef[0];
		if (*root < RAY_T_MIN)
			return (FALSE);
	}
	return (TRUE);
}

static void	save_to_record(t_hit_record *rec, double root,
				const t_ray *ray, t_object *sphere)
{
	t_vector3	origin_to_point;

	rec->t = root;
	rec->point = ray_at(ray, rec->t);
	\
	rec->normal = v_copy(&rec->point);
	v_sub_ip(&rec->normal, &sphere->point);
	v_normalize_ip(&rec->normal);
	\
	origin_to_point = v_copy(&rec->point);
	v_sub_ip(&origin_to_point, &ray->origin);
	if (v_dot(&origin_to_point, &rec->normal) > 0)
		v_scalar_mul_ip(&rec->normal, -1);
	\
	rec->color = sphere->color;
}

// return bool
int	hit_sphere(t_object *sphere, const t_ray *ray, t_hit_record *rec)
{
	double	coef[3];
	double	root;

	calculate_coef(sphere, ray, coef);
	if (!have_root(coef, &root))
		return (FALSE);
	save_to_record(rec, root, ray, sphere);
	return (TRUE);
}
