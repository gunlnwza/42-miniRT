#include "../includes/world.h"

void	add_sphere(t_world *world, const t_vector3 *center, t_decimal radius, int color)
{
	world->spheres[world->nb_spheres] = create_sphere(center, radius, color);
	world->nb_spheres++;
}
