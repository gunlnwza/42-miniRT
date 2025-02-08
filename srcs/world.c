#include "../includes/world.h"

void	init_world(t_world *world)
{
	t_vector3	temp_vector;
	
	world->nb_spheres = 0;

	v_set(&temp_vector, 0, 0, -1);
	add_sphere(world, &temp_vector, 0.5, get_rgba(255, 0, 0, 255));

	v_set(&temp_vector, 0, -100.5, -1);
	add_sphere(world, &temp_vector, 100, get_rgba(0, 255, 0, 255));

	v_set(&temp_vector, 0.5, 0, -1);
	add_sphere(world, &temp_vector, 0.6, get_rgba(0, 0, 255, 255));

	world->ambient_light_color = get_rgba(40, 40, 40, 255);

	world->light.color = get_rgba(100, 100, 100, 255);
	world->light.point = v_create(2, 2, 0);
}

void	add_sphere(t_world *world, const t_vector3 *center, t_decimal radius, int color)
{
	world->spheres[world->nb_spheres] = create_sphere(center, radius, color);
	world->nb_spheres++;
}
