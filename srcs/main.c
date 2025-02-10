/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 13:39:46 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void render_image(mlx_image_t *img, t_world *world, t_camera *camera);

// replace with parser
int	init_world_and_camera(t_world *world, t_camera *camera)
{
	t_vector3	point;
	t_vector3	normal;
	
	world->nb_objects = 0;

	int ambient_I = 50;
	int diffuse_I = 200;

	world->ambient_light_color = get_rgba(ambient_I, ambient_I, ambient_I, 255);

	world->light.color = get_rgba(diffuse_I, diffuse_I, diffuse_I, 255);
	world->light.point = v_create(0, 0, 5);

	// v_set(&point, 0, 0, -1);
	// v_set(&normal, 0, 1, 0.2);
	// double r = 0.5;
	// double h = 0.5;
	// add_cylinder(world, &point, &normal, get_rgba(200, 0, 0, 255), r, h);

	v_set(&point, 0, -2, -2);
	v_set(&normal, 0, 1, 1);
	add_sphere(world, &point, 1, get_rgba(200, 0, 0, 255));

	v_set(&point, 0, -2, -2);
	v_set(&normal, 0, 1, 1);
	add_plane(world, &point, &normal, get_rgba(0, 200, 0, 255));

	v_set(&point, 0, -2, -2);
	v_set(&normal, 1, 0, 1);
	add_plane(world, &point, &normal, get_rgba(0, 0, 200, 255));


	int 		fov;
	// cam_point = v_create(0, 0, 1); cam_normal = v_create(0, 0, -1); fov	= 70;
	// cam_point = v_create(1, 0, 1); cam_normal = v_create(-1, 0, -1); fov = 80;  // yes!! this is correct cylinder!
	point = v_create(1, 5, 30); normal = v_create(-0.5, 0, -1); fov = 60; 
	configure_camera(camera, &point, &normal, fov);
	
	return (SUCCESS);
}


void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	// printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
	(void) mlx;
}

void ft_close(void *param)
{
	exit(0);
	(void) param;
}

void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	(void) param;
}

int	init_display(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (*mlx == NULL)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (ERROR);
	}
	*img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (*img == NULL || (mlx_image_to_window(*mlx, *img, 0, 0) < 0))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (ERROR);
	}
	mlx_close_hook(*mlx, ft_close, NULL);
	mlx_key_hook(*mlx, ft_keypress, NULL);
	mlx_loop_hook(*mlx, ft_hook, *mlx);
	return (SUCCESS);
}


int	main(void)
{
	t_world		world;
	t_camera	camera;
	mlx_t		*mlx;
	mlx_image_t	*img;

	// printf("init_world_and_camera\n");
	if (init_world_and_camera(&world, &camera) == ERROR)  // replace with parser
		return (EXIT_FAILURE);
	mlx = NULL;
	img = NULL;
	// printf("init_display\n");
	if (init_display(&mlx, &img) == ERROR)
		return (EXIT_FAILURE);
	// printf("img = %p", img);
	// printf("render_image\n");
	render_image(img, &world, &camera);
	// printf("mlx_loop\n");
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
