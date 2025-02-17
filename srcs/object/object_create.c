#include "../../includes/object.h"

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
