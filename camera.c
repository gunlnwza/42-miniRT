#include "camera.h"

void	init_camera(t_camera *camera)
{
	float	aspect_ratio;
	aspect_ratio = (float) WIDTH / HEIGHT;
	
	t_vector3	temp_vector;

	float	focal_length;
	focal_length = 1.0f;

	float	viewport_height;
	viewport_height = 2.0f;

	float	viewport_width;
	viewport_width = viewport_height * aspect_ratio;

	v_set(&camera->center, 0, 0, 0);
	v_set(&camera->viewport_h, viewport_width, 0 ,0);
	v_set(&camera->viewport_v, 0, -viewport_height, 0);

	v_copy(&camera->pixel_delta_h, &camera->viewport_h);
	v_scalar_mul(&camera->pixel_delta_h, 1.0f / WIDTH);
	v_copy(&camera->pixel_delta_v, &camera->viewport_v);
	v_scalar_mul(&camera->pixel_delta_v, 1.0f / HEIGHT);

	t_vector3	viewport_upper_left;
	v_copy(&viewport_upper_left, &camera->center);  // camera_center - vec3(0, 0, focal_length) - viewport_h/2 - viewport_v/2;
	v_sub(&viewport_upper_left, v_set(&temp_vector, 0, 0, focal_length));
	v_sub(&viewport_upper_left, v_scalar_mul(v_copy(&temp_vector, &camera->viewport_h), 0.5f));
	v_sub(&viewport_upper_left, v_scalar_mul(v_copy(&temp_vector, &camera->viewport_v), 0.5f));

	v_copy(&camera->pixel00_loc, &viewport_upper_left);
	v_add(&camera->pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &camera->pixel_delta_h), 0.5f));
	v_add(&camera->pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &camera->pixel_delta_v), 0.5f));

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

int	is_ray_hit(const t_world *world, t_ray *ray, float ray_tmin, float ray_tmax, t_hit_record *rec)
{
	t_hit_record	temp_rec;
	int				hit_anything = 0;
	float			closest_so_far = ray_tmax;

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
			}
		}
		i++;
	}
	// (void) closest_so_far;
	return (hit_anything);
}

int	ray_color(t_ray *ray, const t_world *world)
{
	t_hit_record	rec;

	if (is_ray_hit(world, ray, 0, INF, &rec))
	{
		int r = (rec.normal.x + 1) * 0.5 * 255;
		int g = (rec.normal.y + 1) * 0.5 * 255;
		int b = (rec.normal.z + 1) * 0.5 * 255;
		return (get_rgba(r, g, b, 255));
	}
	
	// background
	t_vector3	unit_direction;
	v_copy(&unit_direction, &ray->direction);
	v_normalize(&unit_direction);

	float a = 0.5 * (unit_direction.y + 1.0);
	int r = (1.0 - a) * 255 + a * 0.5 * 255;
	int g = (1.0 - a) * 255 + a * 0.7 * 255;
	int b = (1.0 - a) * 255 + a * 1.0 * 255;
	return (get_rgba(r, g, b, 255));
}
