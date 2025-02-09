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

#include "../includes/mini_rt.h"

void render_image(mlx_image_t *img, t_world *world, t_camera *camera)
{
	t_ray		ray;
	t_vector3	pixel_center;
	int			pixel_color;
	int			x;
	int			y;

	v_copy(&ray.origin, &camera->center);
	v_set(&ray.direction, 0, 0, 0);
	
	v_copy(&pixel_center, &camera->pixel00_loc);

	y = 0;
	while (y < HEIGHT)
	{
		ft_printf("\rRendering: y=%i", y);
		x = 0;
		while (x < WIDTH)
		{
			v_copy(&ray.direction, &pixel_center);
			v_sub(&ray.direction, &camera->center);

		    pixel_color = ray_color(&ray, world);
			mlx_put_pixel(img, x, y, pixel_color);

			x++;
			v_add(&pixel_center, &camera->pixel_delta_h);
		}
		y++;
		v_sub(&pixel_center, &camera->viewport_h);
		v_add(&pixel_center, &camera->pixel_delta_v);
	}
	ft_printf("\rFinish rendering !!!\n");
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	// printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
	(void) mlx;
}

static void ft_close(void *param)
{
	exit(0);
	(void) param;
}

static void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	(void) param;
}

void	init_world(t_world *world)
{
	t_vector3	temp_vector;
	
	world->nb_objects = 0;

	v_set(&temp_vector, 4, 0, -1);
	add_sphere(world, &temp_vector, 0.5, get_rgba(255, 0, 0, 255));

	// v_set(&temp_vector, 0, -100.5, -1);
	// add_sphere(world, &temp_vector, 100, get_rgba(0, 255, 0, 255));

	v_set(&temp_vector, -1, 0, -2);
	add_sphere(world, &temp_vector, 0.6, get_rgba(0, 0, 255, 255));

	v_set(&temp_vector, -4, 0, 1);
	add_sphere(world, &temp_vector, 0.6, get_rgba(0, 200, 200, 255));

	t_vector3	normal = v_create(0, 1, 1);
	v_set(&temp_vector, 0, 0, -2);
	add_plane(world, &temp_vector, &normal, get_rgba(200, 200, 0, 255));

	world->ambient_light_color = get_rgba(42, 42, 42, 255);

	world->light.color = get_rgba(100, 100, 100, 255);
	world->light.point = v_create(-5, 3, 1);
}

int	main(void)
{
	t_world		world;
	t_camera	camera;
	mlx_t		*mlx;
	mlx_image_t	*img;

	init_world(&world);  // replace with parser
	t_vector3	cam_point;
	t_vector3	cam_normal;
	int fov = 70;
	cam_point = v_create(0, 0, 12);
	// cam_normal = v_create(-1, 0, -1);
	cam_normal = v_create(0, 0, -0.8);
	init_camera(&camera, &cam_point, &cam_normal, fov);

	// mlx_set_setting(MLX_MAXIMIZED, true); // set the window to max size on start
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	img = mlx_new_image(mlx, WIDTH, HEIGHT);  // create and display image
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	mlx_close_hook(mlx, ft_close, NULL);
	mlx_key_hook(mlx, ft_keypress, NULL);
	mlx_loop_hook(mlx, ft_hook, mlx);
	render_image(img, &world, &camera);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
