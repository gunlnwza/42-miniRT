/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:28:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:37:13 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/world_and_camera.h"

void	add_sphere(t_world *world, const t_vector3 *center, double radius, int color)
{
	world->objects[world->nb_objects] = create_sphere(center, radius, color);
	world->nb_objects++;
}

void	add_plane(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color)
{
	world->objects[world->nb_objects] = create_plane(point, normal, color);
	world->nb_objects++;
}

void	add_cylinder(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color, double radius, double height)
{
	world->objects[world->nb_objects] = create_cylinder(point, radius, normal, color, height);
	world->nb_objects++;
}

int	init_world_and_camera(t_world *world, t_camera *camera)
{
	t_vector3	point;
	t_vector3	normal;
	int 		fov;
	
	world->nb_objects = 0;

	int ambient_I = 50;
	int diffuse_I = 150;

	world->ambient_light_color = get_rgba(ambient_I, ambient_I, ambient_I, 255);

	world->light.color = get_rgba(diffuse_I, diffuse_I, diffuse_I, 255);
	world->light.point = v_create(0, 2, 0);

	add_sphere(world, v_set(&point, 0, -100.5, -1), 100, get_rgba(0, 0, 200, 255));
	add_sphere(world, v_set(&point, 0, 0, -1), 0.5, get_rgba(200, 0, 0, 255));
	add_sphere(world, v_set(&point, 2, 1, -2), 1, get_rgba(0, 200, 0, 255));
	add_sphere(world, v_set(&point, -2, 2, -2), 1.5, get_rgba(0, 200, 200, 255));

	add_plane(world, v_set(&point, 0, 0, -8), v_set(&normal, 0, 0, 1), get_rgba(200, 200, 0, 255));

	v_set(&point, 0, 0, 1);
	v_normalize(v_set(&normal, -0.1, 0.3, -1));
	fov = 100; 
	configure_camera(camera, &point, &normal, fov);

	return (SUCCESS);
}
