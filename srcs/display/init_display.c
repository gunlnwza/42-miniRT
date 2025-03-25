/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:20:50 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 10:56:25 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/mini_rt.h"

void	ft_close(void *data_)
{
	t_data	*data;

	data = data_;
	mlx_close_window(data->mlx);
}

void	ft_keypress(mlx_key_data_t keydata, void *data_)
{
	t_data		*data;
	t_camera	*camera;
	keys_t		key;

	data = data_;
	camera = &data->world.camera;
	key = keydata.key;
	if (key == MLX_KEY_ESCAPE)
		exit(0);
	if (keydata.action == MLX_PRESS)
	{
		if (is_modify_camera_key(key))
		{
			modify_camera(camera, key);
			printf("\r                                                  ");
			printf("\rC %.2f,%.2f,%.2f %.2f,%.2f,%.2f %i", \
				camera->center.x, camera->center.y, camera->center.z, \
				camera->normal.x, camera->normal.y, camera->normal.z, camera->deg_fov);
		}
		else if (key == MLX_KEY_ENTER)
		{
			printf("\n");
			render_image(data->img, &data->world);
		}
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
		mlx_terminate(data->mlx);
		return (ERROR);
	}
	mlx_close_hook(data->mlx, ft_close, data);
	mlx_key_hook(data->mlx, ft_keypress, data);
	return (SUCCESS);
}
