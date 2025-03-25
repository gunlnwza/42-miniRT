/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:53:16 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 01:40:28 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/t_data.h"

void	init_ray(t_ray *ray, t_camera *camera)
{
	ray->origin = v_copy(&camera->center);
	ray->direction = v_sub(&camera->pixel00_loc, &ray->origin);
}

void	render_image(t_data *data)
{
	t_ray	ray;
	int		pixel_color;
	int		x;
	int		y;

	configure_camera(&data->world.camera);
	init_ray(&ray, &data->world.camera);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_color = ray_color(&ray, &data->world);
			mlx_put_pixel(data->img, x, y, pixel_color);
			x++;
			v_add_ip(&ray.direction, &data->world.camera.pixel_delta_h);
		}
		y++;
		v_sub_ip(&ray.direction, &data->world.camera.viewport_h);
		v_add_ip(&ray.direction, &data->world.camera.pixel_delta_v);
		if (data->mode == MODE_DEBUG)
			printf("\rRendering y=%i", y);
	}
	if (data->mode == MODE_DEBUG)
		printf("\rFinish rendering!\n");
}
