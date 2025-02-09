#include "../includes/world.h"

void	add_sphere(t_world *world, const t_vector3 *center, t_decimal radius, int color)
{
	world->objects[world->nb_objects] = create_sphere(center, radius, color);
	world->nb_objects++;
}

void	add_plane(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color)
{
	world->objects[world->nb_objects] = create_plane(point, normal, color);
	world->nb_objects++;
}

void	add_cylinder(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color, t_decimal radius, t_decimal height)
{
	world->objects[world->nb_objects] = create_cylinder(point, radius, normal, color, height);
	world->nb_objects++;
}
