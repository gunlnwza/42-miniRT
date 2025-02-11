/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:00:13 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	render_image(mlx_image_t *img, t_world *world, t_camera *camera);

// replace with parser
int		init_world_and_camera(t_world *world, t_camera *camera);

typedef struct s_param
{
	mlx_t		**mlx;
	mlx_image_t	**img;
	t_world		*world;
	t_camera	*camera;
}	t_param;

// void	ft_hook(void *param)
// {
// 	const mlx_t	*mlx;

// 	mlx = param;
// 	(void) mlx;
// }

void	ft_close(void *param)
{
	exit(0);
	(void) param;
}

void	ft_keypress(mlx_key_data_t keydata, void *param_)
{
	t_param		*param = param_;
	t_camera	*camera = param->camera;

	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);

	if (keydata.action != MLX_PRESS)
		return ;
	
	float k = 2;
	t_vector3	world_up;
	v_set(&world_up, 0, 1, 0);
	t_vector3	front;
	v_set(&front, camera->normal.x, 0, camera->normal.z);

	if (keydata.key == MLX_KEY_A)
		v_add(&camera->center, v_scalar_mul(v_cross(&world_up, &front), k));
	else if (keydata.key == MLX_KEY_D)
		v_sub(&camera->center, v_scalar_mul(v_cross(&world_up, &front), k));
	else if (keydata.key == MLX_KEY_S)
		v_sub(&camera->center,v_scalar_mul(&front, k));
	else if (keydata.key == MLX_KEY_W)
		v_add(&camera->center, v_scalar_mul(&front, k));
	else if (keydata.key == MLX_KEY_SPACE)
		v_add(&camera->center, v_scalar_mul(&world_up, k));
	else if (keydata.key == MLX_KEY_LEFT_SHIFT)
		v_sub(&camera->center, v_scalar_mul(&world_up, k));
	\
	if (keydata.key == MLX_KEY_UP)
		v_sub(&camera->normal, v_scalar_mul(&camera->viewport_v, 0.2));
	else if (keydata.key == MLX_KEY_DOWN)
		v_add(&camera->normal, v_scalar_mul(&camera->viewport_v, 0.2));
	else if (keydata.key == MLX_KEY_LEFT)
		v_sub(&camera->normal, v_scalar_mul(&camera->viewport_h, 0.2));
	else if (keydata.key == MLX_KEY_RIGHT)
		v_add(&camera->normal, v_scalar_mul(&camera->viewport_h, 0.2));

	if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D
		|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_W
		|| keydata.key == MLX_KEY_SPACE || keydata.key == MLX_KEY_LEFT_SHIFT
		\
		|| keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN
		|| keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
	{
		configure_camera(camera, &camera->center, v_normalize(&camera->normal), camera->deg_fov);
		render_image(*param->img, param->world, camera);	
	}
}

int	init_display(mlx_t **mlx, mlx_image_t **img, t_param *param)
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
	mlx_key_hook(*mlx, ft_keypress, param);
	// mlx_loop_hook(*mlx, ft_hook, param);
	return (SUCCESS);
}

// TODO: replace `init_world_and_camera` with parser
int	main(void)
{
	t_world		world;
	t_camera	camera;
	mlx_t		*mlx;
	mlx_image_t	*img;

	t_param 	param;

	if (init_world_and_camera(&world, &camera) == ERROR)
		return (EXIT_FAILURE);
	mlx = NULL;
	img = NULL;
	param.mlx = &mlx;
	param.img = &img;
	param.world = &world;
	param.camera = &camera;
	if (init_display(&mlx, &img, &param) == ERROR)
		return (EXIT_FAILURE);
	render_image(img, &world, &camera);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
