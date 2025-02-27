/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:44 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/27 10:17:39 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world_and_camera.h"

static void	init_shadow_ray(t_world *world, t_hit_record *rec,
				t_ray *shadow_ray)
{
    shadow_ray->origin = v_copy(&rec->point);
    shadow_ray->direction = v_sub(&world->light.point, &rec->point);
	v_normalize_ip(&shadow_ray->direction);
}

static int	is_light_reach(t_world *world, t_hit_record *rec,
				t_ray *shadow_ray)
{
	t_hit_record	shadow_ray_rec;
	double			int_to_light;
	double			int_to_shadow_ray_int;

	init_shadow_ray(world, rec, shadow_ray);
	if (!is_ray_hit(world, shadow_ray, &shadow_ray_rec))
		return (TRUE);
	int_to_light = v_dist2(&rec->point, &world->light.point);
	int_to_shadow_ray_int = v_dist2(&rec->point, &shadow_ray_rec.point);

    // TODO: This is the troublesome part. Comparing 2 doubles like this is bad, if the two are almost equal (precision errors are what cause the acnes)
	// if (int_to_light < int_to_shadow_ray_int)
		// return (TRUE);

    if (int_to_light - int_to_shadow_ray_int < -0.001)  // int_to_light must be "clearly shorter (more than 0.001 diff)" than int_to_shadow_ray_int
        return (TRUE);

	return (FALSE);
}

static int	calculate_diffuse_color(t_world *world, t_hit_record *rec,
				t_ray *shadow_ray)
{
	double	dot_product;
	int		diffuse_color;

	dot_product = v_dot(&rec->normal, &shadow_ray->direction);
	if (dot_product <= 0)
		return (get_rgba(0, 0, 0, 255));
	diffuse_color = multiply_color(world->light.color, rec->color);
	diffuse_color = get_rgba(
			get_r(diffuse_color) * dot_product,
			get_g(diffuse_color) * dot_product,
			get_b(diffuse_color) * dot_product,
			255);
	return (diffuse_color);
}

int	ray_color(t_ray *ray, t_world *world)
{
	t_hit_record	rec;
	t_ray			shadow_ray;
	int				ambient_color;
	int				diffuse_color;

	if (!is_ray_hit(world, ray, &rec))
		return (get_rgba(0, 0, 0, 255));
	ambient_color = multiply_color(world->ambient_light_color, rec.color);
	if (!is_light_reach(world, &rec, &shadow_ray))
		return (ambient_color);
	diffuse_color = calculate_diffuse_color(world, &rec, &shadow_ray);
	return (add_color(ambient_color, diffuse_color));
}
