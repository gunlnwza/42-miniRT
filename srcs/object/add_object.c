/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:28:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/03 16:44:41 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/world_and_camera.h"

void	add_object(t_world *world, t_object *object)
{
	world->objects[world->nb_objects] = object;
	world->nb_objects++;
}

// TODO: Modify the parser
void	add_sphere(t_world *world, const t_vector3 *center,
			double radius, int color)
{
	world->objects[world->nb_objects] = create_sphere(center, radius, color);
	world->nb_objects++;
}

// TODO: Modify the parser
void	add_plane(t_world *world, const t_vector3 *point,
			const t_vector3 *normal, int color)
{
	world->objects[world->nb_objects] = create_plane(point, normal, color);
	world->nb_objects++;
}

// TODO: Modify the parser
void	add_cylinder(t_world *world, const t_vector3 *point,
			const t_vector3 *normal, int color, double radius, double height)
{
	world->objects[world->nb_objects] = create_cylinder(point, radius, normal, color, height);
	world->nb_objects++;
}

// TODO: Modify the parser
t_object	*create_cylinder(const t_vector3 *point, double radius,
				const t_vector3 *normal, int color, double height)
{
	t_object	*cylinder;

	cylinder = malloc(sizeof(t_object));
	if (cylinder == NULL)
		return (NULL);
	cylinder->type = CYLINDER;
	cylinder->point = v_copy(point);
	cylinder->radius = radius;
	cylinder->normal = v_copy(normal);
	cylinder->color = color;
	cylinder->height = height;
	return (cylinder);
}

// TODO: Modify the parser
t_object	*create_plane(const t_vector3 *point, const t_vector3 *normal,
				int color)
{
	t_object	*plane;

	plane = malloc(sizeof(t_object));
	if (plane == NULL)
		return (NULL);
	plane->type = PLANE;
	plane->point = v_copy(point);
	plane->color = color;
	plane->normal = v_copy(normal);
	return (plane);
}

// TODO: Modify the parser
t_object	*create_sphere(const t_vector3 *center, double radius, int color)
{
	t_object	*sphere;

	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE;
	sphere->point = v_copy(center);
	sphere->color = color;
	sphere->radius = radius;
	return (sphere);
}
