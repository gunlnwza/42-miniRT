/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:53:16 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/03 17:09:35 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world_and_camera.h"

void	init_ray(t_ray *ray, t_camera *camera)
{
	ray->origin = v_copy(&camera->center);
	ray->direction = v_sub(&camera->pixel00_loc, &ray->origin);
}

void	render_image(mlx_image_t *img, t_world *world)
{
	t_ray	ray;
	int		pixel_color;
	int		x;
	int		y;

	configure_camera(&world->camera);
	init_ray(&ray, &world->camera);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_color = ray_color(&ray, world);
			mlx_put_pixel(img, x, y, pixel_color);
			x++;
			v_add_ip(&ray.direction, &world->camera.pixel_delta_h);
		}
		y++;
		v_sub_ip(&ray.direction, &world->camera.viewport_h);
		v_add_ip(&ray.direction, &world->camera.pixel_delta_v);
	}
}
