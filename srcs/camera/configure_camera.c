/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:38:00 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:19:59 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world_and_camera.h"

static void	calculate_viewport_height_and_width(
	int deg_fov, double *vp_height, double *vp_width)
{
	double	aspect_ratio;
	double	rad_fov;

	aspect_ratio = (double) WIDTH / HEIGHT;
	\
	rad_fov = (((double) deg_fov) * PI) / 180;
	*vp_height = 2 * tan(rad_fov / 2);
	*vp_width = (*vp_height) * aspect_ratio;
}

static void	configure_viewport_v_and_h(
	t_camera *camera, const t_vector3 *normal, int deg_fov)
{
	t_vector3	world_up;
	double		vp_width;
	double		vp_height;

	world_up = v_create(0, 1, 0);
	if (fabs(normal->x) < 1e-6 && fabs(normal->z) < 1e-6)
		world_up = v_create(0, 0, 1);
	\
	camera->viewport_h = v_cross(normal, &world_up);
	camera->viewport_v = v_cross(normal, &camera->viewport_h);
	\
	calculate_viewport_height_and_width(deg_fov, &vp_height, &vp_width);
	v_scalar_mul_ip(&camera->viewport_h, vp_width);
	v_scalar_mul_ip(&camera->viewport_v, vp_height);
}

static void	configure_pixel_delta_v_and_h(t_camera *camera)
{
	v_copy_ip(&camera->pixel_delta_h, &camera->viewport_h);
	v_scalar_mul_ip(&camera->pixel_delta_h, 1.0 / WIDTH);
	\
	v_copy_ip(&camera->pixel_delta_v, &camera->viewport_v);
	v_scalar_mul_ip(&camera->pixel_delta_v, 1.0 / HEIGHT);
}

static void	configure_pixel00_loc(t_camera *camera, const t_vector3 *normal)
{
	t_vector3	viewport_upper_left;
	t_vector3	temp;

	v_copy_ip(&viewport_upper_left, &camera->center);
	v_add_ip(&viewport_upper_left, v_normalize_ip(v_copy_ip(&temp, normal)));
	v_sub_ip(&viewport_upper_left,
		v_scalar_mul_ip(v_copy_ip(&temp, &camera->viewport_h), 0.5));
	v_sub_ip(&viewport_upper_left,
		v_scalar_mul_ip(v_copy_ip(&temp, &camera->viewport_v), 0.5));
	\
	v_copy_ip(&camera->pixel00_loc, &viewport_upper_left);
	v_add_ip(&camera->pixel00_loc,
		v_scalar_mul_ip(v_copy_ip(&temp, &camera->pixel_delta_h), 0.5));
	v_add_ip(&camera->pixel00_loc,
		v_scalar_mul_ip(v_copy_ip(&temp, &camera->pixel_delta_v), 0.5));
}

void	configure_camera(
			t_camera *camera, const t_vector3 *point,
			const t_vector3 *normal, int deg_fov)
{
	v_copy_ip(&camera->center, point);
	v_copy_ip(&camera->normal, normal);
	camera->deg_fov = deg_fov;
	configure_viewport_v_and_h(camera, normal, deg_fov);
	configure_pixel_delta_v_and_h(camera);
	configure_pixel00_loc(camera, normal);
}
