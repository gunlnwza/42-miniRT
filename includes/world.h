#ifndef WORLD_H
# define WORLD_H

# include "object.h"
# include "color.h"

typedef struct s_light
{
	int			color;
	t_vector3	point;
}	t_light;

typedef struct s_world
{
	t_object	*objects[10];
	int			nb_objects;

	t_light		light;
	int			ambient_light_color;
}	t_world;

void	add_sphere(t_world *world, const t_vector3 *center, double radius, int color);
void	add_plane(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color);
void	add_cylinder(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color, double radius, double height);

#endif
