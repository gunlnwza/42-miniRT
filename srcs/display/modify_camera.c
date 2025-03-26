/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:48:38 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 10:33:28 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

#define MOVE_DIFF 2

// PI radians == 180 degrees
#define ROTATE_THETA PI / 12

int	is_modify_camera_key(keys_t k)
{
	int	is_move;
	int	is_look;

	is_move = (k == MLX_KEY_SPACE || k == MLX_KEY_LEFT_SHIFT \
		|| k == MLX_KEY_W || k == MLX_KEY_A \
		|| k == MLX_KEY_S || k == MLX_KEY_D);
	is_look = (k == MLX_KEY_UP || k == MLX_KEY_DOWN \
		|| k == MLX_KEY_LEFT || k == MLX_KEY_RIGHT);
	return (is_move || is_look);
}

static void	look_left_right(t_vector3 *normal, double theta)
{
	t_vector3	world_up;
	
	world_up = v_create(0, 1, 0);
	\
	*normal = v_rotate(normal, &world_up, theta);
}

static void look_up_down(t_vector3 *normal, double theta)
{
	t_vector3	world_up;
	t_vector3	front;
	t_vector3	left;
	t_vector3	new_normal;

	world_up = v_create(0, 1, 0);
	front = v_create(normal->x, 0, normal->z);
	left = v_rotate(&front, &world_up, -PI / 2);
	\
	new_normal = v_rotate(normal, &left, theta);
	v_copy_ip(normal, &new_normal);
}

static void	move(t_camera *cam, double front_diff, double left_diff,
				double up_diff)
{
	t_vector3	world_up;
	t_vector3	front;
	t_vector3	left;

	world_up = v_create(0, 1, 0);
	front = v_create(cam->normal.x, 0, cam->normal.z);
	left = v_rotate(&front, &world_up, PI / 2);
	\
	v_scalar_mul_ip(&front, front_diff);
	v_scalar_mul_ip(&left, left_diff);
	v_scalar_mul_ip(&world_up, up_diff);
	\
	v_add_ip(&cam->center, &front);
	v_add_ip(&cam->center, &left);
	v_add_ip(&cam->center, &world_up);
}

void	modify_camera(t_camera *camera, keys_t k)
{
	if (k == MLX_KEY_A)
		move(camera, 0, MOVE_DIFF, 0);
	else if (k == MLX_KEY_D)
		move(camera, 0, -MOVE_DIFF, 0);
	else if (k == MLX_KEY_W)
		move(camera, MOVE_DIFF, 0, 0);
	else if (k == MLX_KEY_S)
		move(camera, -MOVE_DIFF, 0, 0);
	else if (k == MLX_KEY_SPACE)
		move(camera, 0, 0, MOVE_DIFF);
	else if (k == MLX_KEY_LEFT_SHIFT)
		move(camera, 0, 0, -MOVE_DIFF);
	\
	else if (k == MLX_KEY_LEFT)
		look_left_right(&camera->normal, ROTATE_THETA);
	else if (k == MLX_KEY_RIGHT)
		look_left_right(&camera->normal, -ROTATE_THETA);
	else if (k == MLX_KEY_UP)
		look_up_down(&camera->normal, ROTATE_THETA);
	else if (k == MLX_KEY_DOWN)
		look_up_down(&camera->normal, -ROTATE_THETA);
}
