/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 15:52:08 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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

int	ray_color(t_ray *ray)
{
	t_sphere sphere;
	v_set(&sphere.center, 1, 0, -1);
	sphere.radius = 0.5;

	t_hit_record	rec;

	if (hit_sphere(&sphere, ray, 0, 999, &rec))
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

void render_loop(mlx_image_t *img)
{
	// TODO: refactor the viewport setup into functions (implement camera class)
	float	aspect_ratio;
	aspect_ratio = (float) WIDTH / HEIGHT;
	printf("aspect_ratio = %f\n", aspect_ratio);

	float	focal_length;
	float	viewport_height;
	float	viewport_width;
	focal_length = 1.0f;
	viewport_height = 2.0f;
	viewport_width = viewport_height * aspect_ratio;

	t_vector3	camera_center; // the scene camera
	v_set(&camera_center, 0, 0, 0);

	printf("focal_length = %f\n", focal_length);
	printf("viewport_height = %f\nviewport_width = %f\n", viewport_height, viewport_width);
	v_put(&camera_center, "camera_center");
	printf("\n");
	
	t_vector3	viewport_h;
	t_vector3	viewport_v;

	v_set(&viewport_h, viewport_width, 0 ,0);
	v_set(&viewport_v, 0, -viewport_height, 0);

	v_put(&viewport_h, "viewport_h");
	v_put(&viewport_v, "viewport_v");
	printf("\n");

	t_vector3	pixel_delta_h;
	t_vector3	pixel_delta_v;

	v_copy(&pixel_delta_h, &viewport_h);
	v_scalar_mul(&pixel_delta_h, 1.0f / WIDTH);

	v_copy(&pixel_delta_v, &viewport_v);
	v_scalar_mul(&pixel_delta_v, 1.0f / HEIGHT);
	
	v_put(&pixel_delta_h, "pixel_delta_h");
	v_put(&pixel_delta_v, "pixel_delta_v");
	printf("\n");

	t_vector3	temp_vector;
	v_set(&temp_vector, 0, 0, 0);

	t_vector3	viewport_upper_left;
	v_copy(&viewport_upper_left, &camera_center);  // camera_center - vec3(0, 0, focal_length) - viewport_h/2 - viewport_v/2;
	
	v_sub(&viewport_upper_left, v_set(&temp_vector, 0, 0, focal_length));
	v_sub(&viewport_upper_left, v_scalar_mul(v_copy(&temp_vector, &viewport_h), 0.5f));
	v_sub(&viewport_upper_left, v_scalar_mul(v_copy(&temp_vector, &viewport_v), 0.5f));

	v_put(&viewport_upper_left, "viewport_upper_left");
	printf("\n");

	t_vector3	pixel00_loc;
	v_copy(&pixel00_loc, &viewport_upper_left);
	v_add(&pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &pixel_delta_h), 0.5f));
	v_add(&pixel00_loc, v_scalar_mul(v_copy(&temp_vector, &pixel_delta_v), 0.5f));

	v_put(&pixel00_loc, "pixel00_loc");
	printf("\n");

	t_vector3	pixel_center;
	v_copy(&pixel_center, &pixel00_loc);
	v_put(&pixel_center, "pixel_center");
	printf("\n");

	t_ray		ray;
	v_copy(&ray.origin, &camera_center);
	v_set(&ray.direction, 0, 0, 0);
	v_put(&ray.origin, "ray.origin");
	v_put(&ray.direction, "ray.direction");
	printf("\n");

	// render
	int			pixel_color;
	int			x;
	int			y;
	for (y = 0; y < HEIGHT; y++)
	{
		ft_printf("Rendering: y=%i", y);
		for (x = 0; x < WIDTH; x++)
		{
			v_copy(&ray.direction, &pixel_center);
			v_sub(&ray.direction, &camera_center);
			
			// ray is (point=camera_center, dir=ray_direction);  (ray_direction = pixel_center - camera_center)
            pixel_color = ray_color(&ray);
			mlx_put_pixel(img, x, y, pixel_color);
			
			v_add(&pixel_center, &pixel_delta_h);
		}
		ft_printf("                    \r");
		v_sub(&pixel_center, &viewport_h);
		v_add(&pixel_center, &pixel_delta_v);
	}
	ft_printf("Finish rendering\n");
}

int32_t	main(void)
{

	// mlx_set_setting(MLX_MAXIMIZED, true); // set the window to max size on start
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);  // create and display image
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	render_loop(img);

	// Register a hook and pass mlx as an optional param. NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
