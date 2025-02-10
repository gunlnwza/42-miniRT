#include "../../includes/object.h"

t_object    *create_plane(const t_vector3 *point, const t_vector3 *normal, int color)
{
	t_object	*plane;

	plane = malloc(sizeof(t_object));
	if (plane == NULL)
		return (NULL);
	plane->type = PLANE;
	v_copy(&plane->point, point);
	plane->color = color;
	v_copy(&plane->normal, normal);
	return (plane);
}

int	hit_plane(t_object *plane, const t_ray *ray, t_hit_record *rec)
{
	t_decimal ray_tmin = 0.001;
	t_decimal ray_tmax = INF;

	t_vector3	cq;
	t_decimal	root;

	v_copy(&cq, &plane->point);
	v_sub(&cq, &ray->origin);
	root = v_dot(&cq, &plane->normal) / v_dot(&ray->direction, &plane->normal);
	if (root <= ray_tmin || ray_tmax <= root)
		return (0);

	// save to record
	rec->t = root;
	ray_at(ray, rec->t, &rec->point);
	v_copy(&rec->normal, &plane->normal);
	rec->color = plane->color;
	return (1);
}
