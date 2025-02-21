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

void	modify_camera(t_camera *camera, keys_t key)
{
	float		move_mul = 3;
	float		look_mul = 0.3;
	t_vector3	world_up = v_create(0, 1, 0);
	t_vector3	front = v_create(camera->normal.x, 0, camera->normal.z);
	t_vector3	diff;

	if (key == MLX_KEY_A || key == MLX_KEY_D)
	{
		diff = v_cross(&world_up, &front);
		v_scalar_mul_ip(&diff, move_mul);
	}
	else if (key == MLX_KEY_W || key == MLX_KEY_S)
		diff = v_scalar_mul(&front, move_mul);
	else if (key == MLX_KEY_SPACE || key == MLX_KEY_LEFT_SHIFT)
		diff = v_scalar_mul(&world_up, move_mul);
	else if (key == MLX_KEY_UP || key == MLX_KEY_DOWN)
		diff = v_scalar_mul(&camera->viewport_v, look_mul);
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
		diff = v_scalar_mul(&camera->viewport_h, look_mul);
	\
	if (key == MLX_KEY_A || key == MLX_KEY_W || key == MLX_KEY_SPACE)
		v_add_ip(&camera->center, &diff);
	else if (key == MLX_KEY_D || key == MLX_KEY_S || key == MLX_KEY_LEFT_SHIFT)
		v_sub_ip(&camera->center, &diff);
	else if (key == MLX_KEY_UP || key == MLX_KEY_LEFT)
		v_sub_ip(&camera->normal, &diff);
	else if (key == MLX_KEY_DOWN || key == MLX_KEY_RIGHT)
		v_add_ip(&camera->normal, &diff);
	v_normalize_ip(&camera->normal);

	dprintf(2, "configure_camera(camera, v_set_ip(&P, %.2f, %.2f, %.2f), v_normalize_ip(v_set_ip(&N, %.2f, %.2f, %.2f)), fov);\n",
			camera->center.x, camera->center.y, camera->center.z, camera->normal.x, camera->normal.y, camera->normal.z);
}

int	is_modify_camera_key(keys_t key)
{
	return (key == MLX_KEY_A || key == MLX_KEY_D || key == MLX_KEY_S || key == MLX_KEY_W
		|| key == MLX_KEY_SPACE || key == MLX_KEY_LEFT_SHIFT
		|| key == MLX_KEY_UP || key == MLX_KEY_DOWN || key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT
		|| key == MLX_KEY_ENTER);
}

void	ft_keypress(mlx_key_data_t keydata, void *param_)
{
	// (void) param_;
	t_param		*param = param_;
	t_camera	*camera = param->camera;

	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	\
	if (keydata.action != MLX_PRESS)
		return ;
	if (!is_modify_camera_key(keydata.key))
		return ;
	\
	modify_camera(camera, keydata.key);
	if (keydata.key == MLX_KEY_ENTER)
	{
		configure_camera(camera, &camera->center, &camera->normal, camera->deg_fov);
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
int	main(int argc, char **argv)
{
	t_world		world;
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_param 	param;

	ft_bzero(&world, sizeof(t_world));
	if (argc != 2 || open_file(&world, argv[1]) != 0)
	{
        ft_putstr_fd("Error: Invalid scene file\n", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
	mlx = NULL;
	img = NULL;
	param.mlx = &mlx;
	param.img = &img;
	param.world = &world;
	param.camera = &world.camera;
	if (init_display(&mlx, &img, &param) == ERROR)
		return (EXIT_FAILURE);
	configure_camera(&world.camera, &world.camera.center, &world.camera.normal, world.camera.deg_fov);
	render_image(img, &world, &world.camera);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
