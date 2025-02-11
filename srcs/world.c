/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:28:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:07:37 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/world_and_camera.h"

// will be replaced with parser later

void	add_sphere(t_world *world, const t_vector3 *center,
			double radius, int color)
{
	world->objects[world->nb_objects] = create_sphere(center, radius, color);
	world->nb_objects++;
}

void	add_plane(t_world *world, const t_vector3 *point,
			const t_vector3 *normal, int color)
{
	world->objects[world->nb_objects] = create_plane(point, normal, color);
	world->nb_objects++;
}

void	add_cylinder(t_world *world, const t_vector3 *point,
			const t_vector3 *normal, int color, double radius, double height)
{
	world->objects[world->nb_objects] = \
		create_cylinder(point, radius, normal, color, height);
	world->nb_objects++;
}

/*
TODO:
Using parser will allow us to create object on the go,
meaning we won't have to rely on norm-error funcs, like create_cylinder()
*/
int	init_world_and_camera(t_world *world, t_camera *camera)
{
	t_vector3	P;
	t_vector3	N;
	int			fov;
	int			ambient_intensity;
	int			diffuse_intensity;

	world->nb_objects = 0;
	\
	ambient_intensity = 70;
	diffuse_intensity = 200;
	\
	world->ambient_light_color = get_rgba(
		ambient_intensity, ambient_intensity, ambient_intensity, 255);
	\
	world->light.color = get_rgba(
		diffuse_intensity, diffuse_intensity, diffuse_intensity, 255);
	world->light.point = v_create(0, 4, 10);
	\
	add_sphere(world, v_set(&P, 0, -100, 0), 100, get_rgba(0, 0, 200, 255));
	\
	add_plane(world, v_set(&P, 0, 0, -10), v_normalize(v_set(&N, -1, -1, -1)), get_rgba(200, 200, 0, 255));
	\
	add_cylinder(world, v_set(&P, 0, 0, 0), v_normalize(v_set(&N, 0, 1, 0)), get_rgba(200, 0, 200, 255), 0.5, 10);
	\
	fov = 45;
	// configure_camera(camera, v_set(&P, 28.6, 8, 33.4), v_normalize(v_set(&N, -0.8, -0.15, -0.55)), fov);
	// configure_camera(camera, v_set(&P, 0, 1, 2), v_normalize(v_set(&N, 0, 0, -1)), fov);
	configure_camera(camera, v_set(&P, 2, 4, 10), v_normalize(v_set(&N, 0, 0, -1)), fov);
	return (SUCCESS);
}

/*
camera.center = (28.626529, 8.000000, 33.423184)
camera.normal = (-0.816260, -0.149902, -0.557897)
*/

/*
camera.center = (3.122321, 1.000000, 0.344586)
camera.normal = (-0.994143, 0.000000, -0.108071)
*/