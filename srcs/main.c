/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 15:15:50 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void render_image(mlx_image_t *img, t_world *world, t_camera *camera);

// replace with parser
int	init_world_and_camera(t_world *world, t_camera *camera)
{
	t_vector3	point;
	t_vector3	normal;
	int 		fov;
	
	world->nb_objects = 0;

	int ambient_I = 50;
	int diffuse_I = 150;

	world->ambient_light_color = get_rgba(ambient_I, ambient_I, ambient_I, 255);

	world->light.color = get_rgba(diffuse_I, diffuse_I, diffuse_I, 255);
	world->light.point = v_create(0, 5, 0);

	add_sphere(world, v_set(&point, 0, -100.5, -1), 100, get_rgba(0, 0, 200, 255));
	// add_sphere(world, v_set(&point, 0, 0, -1), 0.5, get_rgba(200, 0, 0, 255));
	// add_sphere(world, v_set(&point, 2, 1, -2), 1, get_rgba(0, 200, 0, 255));
	// add_sphere(world, v_set(&point, -2, 2, -2), 1.5, get_rgba(0, 200, 200, 255));

	add_plane(world, v_set(&point, 0, 0, -8), v_set(&normal, 0, 0, 1), get_rgba(200, 200, 0, 255));

	v_set(&point, 0, 0, 1);
	v_normalize(v_set(&normal, -0.1, 0.3, -1));
	fov = 100; 
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
