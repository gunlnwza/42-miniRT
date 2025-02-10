/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:50:44 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 17:40:56 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world_and_camera.h"

static int get_normal_color(t_vector3 *normal)
{
	int r = (normal->x + 1) * 0.5 * 255; 
	int g = (normal->y + 1) * 0.5 * 255; 
	int b = (normal->z + 1) * 0.5 * 255;
	return (get_rgba(r, g, b, 255));
}

static int	is_shadow_ray_hit(t_world *world, t_hit_record *rec,
				t_ray *shadow_ray, t_hit_record *shadow_ray_rec)
{
	shadow_ray->origin = rec->point;
	v_copy(&shadow_ray->direction, &world->light.point);
	v_sub(&shadow_ray->direction, &rec->point);
	v_normalize(&shadow_ray->direction);
	return (is_ray_hit(world, shadow_ray, shadow_ray_rec));
}

static int	calculate_diffuse_color(t_world *world, t_hit_record *rec,
				t_ray *shadow_ray)
{
	int		diffuse_color;
	double	dot_product;

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
	int				ambient_color;
	int				diffuse_color;
	t_ray			shadow_ray;
	t_hit_record	shadow_ray_rec;

	if (!is_ray_hit(world, ray, &rec))
		return (get_rgba(0, 0, 0, 255));
	return (get_normal_color(&rec.normal));
	ambient_color = multiply_color(world->ambient_light_color, rec.color);
	if (is_shadow_ray_hit(world, &rec, &shadow_ray, &shadow_ray_rec))
		return (ambient_color);
	diffuse_color = calculate_diffuse_color(world, &rec, &shadow_ray);
	return (add_color(ambient_color, diffuse_color));
}
