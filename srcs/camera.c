#include "../includes/camera.h"
#include <stdio.h>

void	calculate_and_set_camera(t_camera *camera, const t_vector3 *point, const t_vector3 *normal, int deg_fov)
{
	t_vector3	temp_vector;
	t_decimal	aspect_ratio;
	t_decimal	viewport_height;
	t_decimal	viewport_width;
	t_vector3	viewport_upper_left;

	aspect_ratio = (t_decimal) WIDTH / HEIGHT;
	double rad_fov = ((double) deg_fov * PI) / 180;
	viewport_height = 2 * tan(rad_fov / 2);
	viewport_width = viewport_height * aspect_ratio;

	// camera center
	v_copy(&camera->center, point);

	// viewport h, v
	// v_set(&camera->viewport_h, viewport_width, 0, 0);
	// v_set(&camera->viewport_v, 0, -viewport_height, 0);

	t_vector3	new_right;
	t_vector3	new_up;
	t_vector3	world_up = v_create(0, 1, 0);
	if (fabs(normal->x) < 1e-6 && fabs(normal->z) < 1e-6)
		world_up = v_create(0, 0, 1);

	v_copy(&new_right, normal);
	v_cross(&new_right, &world_up);

	v_copy(&new_up, normal);
	v_cross(&new_up, &new_right);

	v_copy(&camera->viewport_h, &new_right);
	v_scalar_mul(&camera->viewport_h, viewport_width);
	v_copy(&camera->viewport_v, &new_up);
	v_scalar_mul(&camera->viewport_v, viewport_height);

	// pixel_delta_h, pixel_delta_v
	v_copy(&camera->pixel_delta_h, &camera->viewport_h);
	v_scalar_mul(&camera->pixel_delta_h, 1.0 / WIDTH);
	v_copy(&camera->pixel_delta_v, &camera->viewport_v);
	v_scalar_mul(&camera->pixel_delta_v, 1.0 / HEIGHT);

	// viewport_upper_left
	v_copy(&viewport_upper_left, &camera->center);

	v_copy(&temp_vector, normal);
	v_normalize(&temp_vector);
	v_add(&viewport_upper_left, &temp_vector);
	
	v_copy(&temp_vector, &camera->viewport_h);
	v_sub(&viewport_upper_left, v_scalar_mul(&temp_vector, 0.5));
	
	v_copy(&temp_vector, &camera->viewport_v);
	v_sub(&viewport_upper_left, v_scalar_mul(&temp_vector, 0.5));

	// pixel_00
	v_copy(&camera->pixel00_loc, &viewport_upper_left);
	v_add(&camera->pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &camera->pixel_delta_h), 0.5));
	v_add(&camera->pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &camera->pixel_delta_v), 0.5));

	// debug
	// printf("Debug!!!\n");
	// printf("aspect_ratio = %f\n", aspect_ratio);
	// printf("focal_length = %f\n", focal_length);
	
	printf("deg_fov = %d\n", deg_fov);
	printf("viewport_height = %f\nviewport_width = %f\n", viewport_height, viewport_width);
	// v_put(&camera_center, "camera_center");
	printf("\n");
	v_put(&camera->viewport_h, "viewport_h");
	v_put(&camera->viewport_v, "viewport_v");
	printf("\n");
	// v_put(&pixel_delta_h, "pixel_delta_h");
	// v_put(&pixel_delta_v, "pixel_delta_v");
	// printf("\n");
	// v_put(&viewport_upper_left, "viewport_upper_left");
	// printf("\n");
	// v_put(&pixel00_loc, "pixel00_loc");
	// printf("\n");
	// v_put(&pixel_center, "pixel_center");
	// printf("\n");
	// v_put(&ray.origin, "ray.origin");
	// v_put(&ray.direction, "ray.direction");
	// printf("\n");
}

int	is_ray_hit(const t_world *world, t_ray *ray, t_decimal ray_tmin, t_decimal ray_tmax, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	int				hit_anything;
	t_decimal		closest_so_far;
	int				i;
	int				ret;

	hit_anything = 0;
	closest_so_far = ray_tmax;
	i = 0;
	while (i < world->nb_objects)
	{

		if (world->objects[i]->type == SPHERE)
		{
			// printf("Sp ");
			ret = hit_sphere(world->objects[i], ray, ray_tmin, ray_tmax, &temp_rec);
		}
		else if (world->objects[i]->type == PLANE)
		{
			// printf("Pl ");
			ret = hit_plane(world->objects[i], ray, ray_tmin, ray_tmax, &temp_rec);
		}
		else
		{
			// printf("Cy ");
			ret = hit_cylinder(world->objects[i], ray, ray_tmin, ray_tmax, &temp_rec);
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

int	ray_color(t_ray *ray, const t_world *world)
{
	t_hit_record	rec;
	int				ambient_color, diffuse_color;
	int				color;

	if (!is_ray_hit(world, ray, 0.001, INF, &rec))
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
	if (is_ray_hit(world, &shadow_ray, 0.001f, INF, &shadow_ray_rec))
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
