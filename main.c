/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/07 17:42:42 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void render_loop(mlx_image_t *img)
{
	t_world		world;
	init_world(&world);

	t_camera	camera;
	int			max_depth = 50;
	init_camera(&camera);

	t_ray		ray;
	v_copy(&ray.origin, &camera.center);
	v_set(&ray.direction, 0, 0, 0);
	
	t_vector3	pixel_center;
	v_copy(&pixel_center, &camera.pixel00_loc);
	
	int			pixel_color;
	int			x;
	int			y;

	for (y = 0; y < HEIGHT; y++)
	{
		ft_printf("\rRendering: y=%i", y);
		for (x = 0; x < WIDTH; x++)
		{
			v_copy(&ray.direction, &pixel_center);
			v_sub(&ray.direction, &camera.center);

		    pixel_color = ray_color(&ray, max_depth, &world);
			mlx_put_pixel(img, x, y, pixel_color);

			v_add(&pixel_center, &camera.pixel_delta_h);
		}
		v_sub(&pixel_center, &camera.viewport_h);
		v_add(&pixel_center, &camera.pixel_delta_v);
	}
	ft_printf("\rFinish rendering !!!\n");
}

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

int	main(void)
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

