/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:48:38 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/03 17:18:31 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

#define MOVE_MUL 1
#define LOOK_MUL 0.2

int	is_modify_camera_key(keys_t key)
{
	int	is_move;
	int	is_look;

	is_move = (key == MLX_KEY_SPACE || key == MLX_KEY_LEFT_SHIFT \
		|| key == MLX_KEY_W || key == MLX_KEY_A \
		|| key == MLX_KEY_S || key == MLX_KEY_D);
	is_look = (key == MLX_KEY_UP || key == MLX_KEY_DOWN \
		|| key == MLX_KEY_LEFT || key == MLX_KEY_RIGHT);
	return (is_move || is_look);
}

static t_vector3	get_diff(t_camera *camera, keys_t key)
{
	t_vector3	world_up;
	t_vector3	front;
	t_vector3	diff;

	world_up = v_create(0, 1, 0);
	front = v_create(camera->normal.x, 0, camera->normal.z);
	diff = v_create(0, 0, 0);
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
	return (diff);
}

void	modify_camera(t_camera *camera, keys_t key)
{
	t_vector3	diff;

	diff = get_diff(camera, key);
	if (key == MLX_KEY_A || key == MLX_KEY_W || key == MLX_KEY_SPACE)
		v_add_ip(&camera->center, &diff);
	else if (key == MLX_KEY_D || key == MLX_KEY_S || key == MLX_KEY_LEFT_SHIFT)
		v_sub_ip(&camera->center, &diff);
	else if (key == MLX_KEY_UP || key == MLX_KEY_LEFT)
		v_sub_ip(&camera->normal, &diff);
	else if (key == MLX_KEY_DOWN || key == MLX_KEY_RIGHT)
		v_add_ip(&camera->normal, &diff);
	v_normalize_ip(&camera->normal);
}
