#include "world.h"

void	init_world(t_world *world)
{
	t_vector3	temp_vector;
	
	world->nb_spheres = 0;

	v_set(&temp_vector, 0, 0, -1);
	add_sphere(world, &temp_vector, 0.5);

	v_set(&temp_vector, 0, -100.5, -1);
	add_sphere(world, &temp_vector, 100);
}

void	add_sphere(t_world *world, const t_vector3 *center, float radius)
{
	world->spheres[world->nb_spheres] = create_sphere(center, radius);
	world->nb_spheres++;
}
