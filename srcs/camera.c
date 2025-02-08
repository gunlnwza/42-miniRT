#include "../includes/camera.h"

void	init_camera(t_camera *camera)
{
	t_decimal	aspect_ratio;
	aspect_ratio = (t_decimal) WIDTH / HEIGHT;
	
	t_vector3	temp_vector;

	t_decimal	focal_length;
	focal_length = 1.0;

	t_decimal	viewport_height;
	viewport_height = 2.0;

	t_decimal	viewport_width;
	viewport_width = viewport_height * aspect_ratio;

	v_set(&camera->center, 0, 0, 0);
	v_set(&camera->viewport_h, viewport_width, 0 ,0);
	v_set(&camera->viewport_v, 0, -viewport_height, 0);

	v_copy(&camera->pixel_delta_h, &camera->viewport_h);
	v_scalar_mul(&camera->pixel_delta_h, 1.0 / WIDTH);
	v_copy(&camera->pixel_delta_v, &camera->viewport_v);
	v_scalar_mul(&camera->pixel_delta_v, 1.0 / HEIGHT);

	t_vector3	viewport_upper_left;
	v_copy(&viewport_upper_left, &camera->center);  // camera_center - vec3(0, 0, focal_length) - viewport_h/2 - viewport_v/2;
	v_sub(&viewport_upper_left, v_set(&temp_vector, 0, 0, focal_length));
	v_sub(&viewport_upper_left, v_scalar_mul(v_copy(&temp_vector, &camera->viewport_h), 0.5));
	v_sub(&viewport_upper_left, v_scalar_mul(v_copy(&temp_vector, &camera->viewport_v), 0.5));

	v_copy(&camera->pixel00_loc, &viewport_upper_left);
	v_add(&camera->pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &camera->pixel_delta_h), 0.5));
	v_add(&camera->pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &camera->pixel_delta_v), 0.5));

	// debug
	// printf("Debug!!!\n");
	// printf("aspect_ratio = %f\n", aspect_ratio);
	// printf("focal_length = %f\n", focal_length);
	// printf("viewport_height = %f\nviewport_width = %f\n", viewport_height, viewport_width);
	// v_put(&camera_center, "camera_center");
	// printf("\n");
	// v_put(&viewport_h, "viewport_h");
	// v_put(&viewport_v, "viewport_v");
	// printf("\n");
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
	int				hit_anything = 0;
	t_decimal		closest_so_far = ray_tmax;

	int i = 0;
	while (i < world->nb_spheres)
	{
		if (hit_sphere(world->spheres[i], ray, ray_tmin, ray_tmax, &temp_rec))
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
	// (void) closest_so_far;
	return (hit_anything);
}

void	random_on_hemisphere(t_vector3 *dest, const t_vector3 *normal)
{
	t_vector3	on_unit_sphere;
	float		length_squared;

	while (1)
	{
		v_set(&on_unit_sphere, ft_random(), ft_random(), ft_random());
		length_squared = v_norm2(&on_unit_sphere);
		if (1e-160 < length_squared && length_squared <= 1)
		{
			v_normalize(&on_unit_sphere);
			break ;
		}
	}

	if (v_dot(&on_unit_sphere, normal) > 0.0)
	{
		v_copy(dest, &on_unit_sphere);
	}
	else
	{
		v_copy(dest, v_scalar_mul(&on_unit_sphere, -1));
	}
}

int	ray_color(t_ray *ray, const t_world *world)
{
	int				r,g,b;
	// int 			color;
	t_hit_record	rec;

	t_decimal a;

	if (is_ray_hit(world, ray, 0.001, INF, &rec))
	{
		// r = (rec.normal.x + 1) * 0.5 * 255; g = (rec.normal.y + 1) * 0.5 * 255; b = (rec.normal.z + 1) * 0.5 * 255; color = get_rgba(r, g, b, 255);

		t_vector3	direction;
		// random_on_hemisphere(&direction, &rec.normal);
		v_set(&direction, ft_random(), ft_random(), ft_random());
		v_add(&direction, &rec.normal);

		t_ray	new_ray;
		new_ray.origin = rec.point;
		v_copy(&new_ray.direction, &direction);

		a = 0.5;
		// return ((1 - a) * rec.color + a * ray_color(&new_ray, depth - 1, world));
		return (ray_color(&new_ray, world));
	}
	
	// background
	t_vector3	unit_direction;
	v_copy(&unit_direction, &ray->direction);
	v_normalize(&unit_direction);

	a = 0.5 * (unit_direction.y + 1.0);
	r = (1.0 - a) * 255 + a * 0.5 * 255; g = (1.0 - a) * 255 + a * 0.7 * 255; b = (1.0 - a) * 255 + a * 1.0 * 255;
	return (get_rgba(r, g, b, 255));
}
