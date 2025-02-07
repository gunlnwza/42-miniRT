#ifndef WORLD_H
# define WORLD_H

# include "sphere.h"

typedef struct s_world
{
	t_sphere	*spheres[10];
	int			nb_spheres;
}	t_world;

void	init_world(t_world *world);
void	add_sphere(t_world *world, const t_vector3 *center, float radius);

#endif
