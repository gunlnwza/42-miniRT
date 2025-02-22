/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:20:50 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/22 13:21:06 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

#define MOVE_MUL 3
#define LOOK_MUL 0.3

void	modify_camera(t_camera *camera, keys_t key)
{
	t_vector3	world_up;
	t_vector3	front;
	t_vector3	diff;

	world_up = v_create(0, 1, 0);
	front = v_create(camera->normal.x, 0, camera->normal.z);
	\
	if (key == MLX_KEY_A || key == MLX_KEY_D)
	{
		diff = v_cross(&world_up, &front);
		v_scalar_mul_ip(&diff, MOVE_MUL);
	}
	else if (key == MLX_KEY_W || key == MLX_KEY_S)
		diff = v_scalar_mul(&front, MOVE_MUL);
	else if (key == MLX_KEY_SPACE || key == MLX_KEY_LEFT_SHIFT)
		diff = v_scalar_mul(&world_up, MOVE_MUL);
	else if (key == MLX_KEY_UP || key == MLX_KEY_DOWN)
		diff = v_scalar_mul(&camera->viewport_v, LOOK_MUL);
	else if (key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT)
		diff = v_scalar_mul(&camera->viewport_h, LOOK_MUL);
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
	\
	dprintf(2, "C %.2f,%.2f,%.2f %.2f,%.2f,%.2f %i\n", \
		camera->center.x, camera->center.y, camera->center.z, \
		camera->normal.x, camera->normal.y, camera->normal.z, camera->deg_fov);
}

int	is_modify_camera_key(keys_t key)
{
	int	is_move;
	int	is_look;

	is_move = (key == MLX_KEY_SPACE || key == MLX_KEY_LEFT_SHIFT \
		|| key == MLX_KEY_W || key == MLX_KEY_A \
		|| key == MLX_KEY_S || key == MLX_KEY_D);
	is_look = (key == MLX_KEY_UP || key == MLX_KEY_DOWN \
		|| key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT);
	return (is_move || is_look || key == MLX_KEY_ENTER);
}

void	ft_close(void *param)
{
	t_data	*data;

	data = param;
	(void) data;
	exit(0);
}

void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	t_data		*data;
	t_camera	*camera;

	data = param;
	camera = &data->world.camera;
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	\
	if (!(keydata.action == MLX_PRESS && is_modify_camera_key(keydata.key)))
		return ;
	modify_camera(camera, keydata.key);
	if (keydata.key == MLX_KEY_ENTER)
	{
		configure_camera(camera);
		render_image(data->img, &data->world);
	}
}

int	init_display(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (data->mlx == NULL)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (ERROR);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img == NULL
		|| (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (ERROR);
	}
	mlx_close_hook(data->mlx, ft_close, data);
	mlx_key_hook(data->mlx, ft_keypress, data);
	return (SUCCESS);
}
