#include "../../includes/camera.h"

int	ray_color(t_ray *ray, const t_world *world)
{
	t_hit_record	rec;
	int				ambient_color, diffuse_color;
	int				color;

	if (!is_ray_hit(world, ray, &rec))
		return (get_rgba(0, 0, 0, 255));

	// // make normal vector color
	// int r = (rec.normal.x + 1) * 0.5 * 255; 
	// int g = (rec.normal.y + 1) * 0.5 * 255; 
	// int b = (rec.normal.z + 1) * 0.5 * 255;
	// color = get_rgba(r, g, b, 255);
	
	ambient_color = multiply_color(world->ambient_light_color, rec.color);

	// insert shadow
	t_ray			shadow_ray;
	t_hit_record	shadow_ray_rec;
	shadow_ray.origin = rec.point;
	v_copy(&shadow_ray.direction, &world->light.point);
	v_sub(&shadow_ray.direction, &rec.point);
	v_normalize(&shadow_ray.direction);
	if (is_ray_hit(world, &shadow_ray, &shadow_ray_rec))
		return (ambient_color);
	// is_ray_hit(world, &shadow_ray, 0.001, INF, &shadow_ray_rec);

	t_decimal	dot_product = v_dot(&rec.normal, &shadow_ray.direction);
	if (dot_product > 0)
	{
		diffuse_color = multiply_color(world->light.color, rec.color);
		diffuse_color = get_rgba(get_r(diffuse_color) * dot_product, get_g(diffuse_color) * dot_product, get_b(diffuse_color) * dot_product, 255);
	}
	else
		diffuse_color = get_rgba(0, 0, 0, 255);
	color = add_color(ambient_color, diffuse_color);
	return (color);
}
