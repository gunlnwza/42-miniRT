/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 14:31:08 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#define WIDTH 800
#define HEIGHT 600

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	// printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
	(void) mlx;
}

int hit_sphere(const t_vector3 *center, float radius, const t_ray *ray)
{
	t_vector3	oc;
	vector3_copy_ip(&oc, center);
	vector3_sub_ip(&oc, &ray->origin);

	float a = vector3_dot(&ray->direction, &ray->direction);
	float b = -2.0 * vector3_dot(&ray->direction, &oc);
	float c = vector3_dot(&oc, &oc) - radius * radius;
	
	float discriminant = b*b - 4*a*c;
	return (discriminant >= 0);
}

int	ray_color(t_ray *ray)
{
	t_vector3	point;
	vector3_set_values_ip(&point, -1, 1, 1);
	if (hit_sphere(&point, 1, ray))
		return (get_rgba(255, 0, 0, 255));

	t_vector3	unit_direction;
	vector3_copy_ip(&unit_direction, &ray->direction);
	vector3_normalize_ip(&unit_direction);

	float a = 0.5 * (unit_direction.y + 1.0);

	int r;
	int g;
	int b;

	r = (1.0 - a) * 255 + a * 0.5 * 255;
	g = (1.0 - a) * 255 + a * 0.7 * 255;
	b = (1.0 - a) * 255 + a * 1.0 * 255;

	return (get_rgba(r, g, b, 255));
}


int32_t	main(void)
{
	float	aspect_ratio = (float) WIDTH / HEIGHT;
	printf("float aspect_ratio = %f\n", aspect_ratio);

	float		focal_length = 1.0f;
	float		viewport_height = 2.0f;
	float		viewport_width = viewport_height * aspect_ratio;
	t_vector3	*camera_center = vector3_create(0, 0, 0);  // the scene camera
	
	t_vector3	*viewport_h = vector3_create(viewport_width, 0 ,0);
	t_vector3	*viewport_v = vector3_create(0, -viewport_height ,0);

	t_vector3	*pixel_delta_h = vector3_copy(viewport_h);
	vector3_scalar_mul_ip(pixel_delta_h, 1.0f / WIDTH);
	
	t_vector3	*pixel_delta_v = vector3_copy(viewport_v);
	vector3_scalar_mul_ip(pixel_delta_v, 1.0f / HEIGHT);

	t_vector3	*temp_vector = vector3_create(0, 0, 0);

	t_vector3	*viewport_upper_left = vector3_copy(camera_center);
	
	vector3_set_values_ip(temp_vector, 0, 0, focal_length);
	vector3_sub_ip(viewport_upper_left, temp_vector);

	vector3_copy_ip(temp_vector, viewport_h);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_sub_ip(viewport_upper_left, temp_vector);
	
	vector3_copy_ip(temp_vector, viewport_v);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_sub_ip(viewport_upper_left, temp_vector);

	t_vector3	*pixel00_loc = vector3_copy(viewport_upper_left);

	vector3_copy_ip(temp_vector, pixel_delta_h);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_add_ip(pixel00_loc, temp_vector);
	
	vector3_copy_ip(temp_vector, pixel_delta_v);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_add_ip(pixel00_loc, temp_vector);

	t_vector3	*pixel_center = vector3_copy(pixel00_loc);

	t_ray		ray;
	vector3_copy_ip(&ray.origin, pixel_center);
	vector3_set_values_ip(&ray.direction, 0, 0, 0);

	int			pixel_color;
	int			x;
	int			y;

	// mlx_set_setting(MLX_MAXIMIZED, true); // set the window to max size on start
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);  // create and display image
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	for (y = 0; y < HEIGHT; y++)
	{
		ft_printf("Rendering: y=%i", y);
		for (x = 0; x < WIDTH; x++)
		{
			vector3_copy_ip(&ray.direction, pixel_center);
			vector3_sub_ip(&ray.direction, camera_center);
			
			// ray is (point=camera_center, dir=ray_direction);  (ray_direction = pixel_center - camera_center)
            pixel_color = ray_color(&ray);
			mlx_put_pixel(img, x, y, pixel_color);
			
			vector3_add_ip(pixel_center, pixel_delta_h);
		}
		ft_printf("                    \r");
		vector3_sub_ip(pixel_center, viewport_h);
		vector3_add_ip(pixel_center, pixel_delta_v);
	}
	ft_printf("Finish rendering\n");

	// Register a hook and pass mlx as an optional param. NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
