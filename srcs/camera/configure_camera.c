/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:38:00 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 13:47:13 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/camera.h"

static void	configure_viewport_v_and_h(
				t_camera *camera, const t_vector3 *normal, int deg_fov)
{
	t_vector3	world_up;
	t_decimal	aspect_ratio;
	t_decimal	viewport_width;
	t_decimal	viewport_height;
	t_decimal	rad_fov;

	world_up = v_create(0, 1, 0);
	if (fabs(normal->x) < 1e-6 && fabs(normal->z) < 1e-6)
		world_up = v_create(0, 0, 1);
	\
	v_cross(v_copy(&camera->viewport_h, normal), &world_up);
	v_cross(v_copy(&camera->viewport_v, normal), &camera->viewport_h);
	\
	aspect_ratio = (t_decimal) WIDTH / HEIGHT;
	rad_fov = (((double) deg_fov) * PI) / 180;
	viewport_height = 2 * tan(rad_fov / 2);
	viewport_width = viewport_height * aspect_ratio;
	v_scalar_mul(&camera->viewport_h, viewport_width);
	v_scalar_mul(&camera->viewport_v, viewport_height);
}

static void	configure_pixel_delta_v_and_h(t_camera *camera)
{
	v_copy(&camera->pixel_delta_h, &camera->viewport_h);
	v_scalar_mul(&camera->pixel_delta_h, 1.0 / WIDTH);
	v_copy(&camera->pixel_delta_v, &camera->viewport_v);
	v_scalar_mul(&camera->pixel_delta_v, 1.0 / HEIGHT);
}

static void	configure_pixel00_loc(t_camera *camera, const t_vector3 *normal)
{
	t_vector3	viewport_upper_left;
	t_vector3	temp;

	v_copy(&viewport_upper_left, &camera->center);
	v_add(&viewport_upper_left, v_normalize(v_copy(&temp, normal)));
	v_sub(&viewport_upper_left,
		v_scalar_mul(v_copy(&temp, &camera->viewport_h), 0.5));
	v_sub(&viewport_upper_left,
		v_scalar_mul(v_copy(&temp, &camera->viewport_v), 0.5));
	\
	v_copy(&camera->pixel00_loc, &viewport_upper_left);
	v_add(&camera->pixel00_loc,
		v_scalar_mul(v_copy(&temp, &camera->pixel_delta_h), 0.5));
	v_add(&camera->pixel00_loc,
		v_scalar_mul(v_copy(&temp, &camera->pixel_delta_v), 0.5));
}

void	configure_camera(
			t_camera *camera, const t_vector3 *point,
			const t_vector3 *normal, int deg_fov)
{
	v_copy(&camera->center, point);
	configure_viewport_v_and_h(camera, normal, deg_fov);
	configure_pixel_delta_v_and_h(camera);
	configure_pixel00_loc(camera, normal);
}
