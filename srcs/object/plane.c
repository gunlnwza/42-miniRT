#include "../../includes/object.h"

t_object	*create_plane(const t_vector3 *point, const t_vector3 *normal, int color)
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

static void	save_to_record(t_hit_record *rec, double root,
				const t_ray *ray, t_object *plane)
{
	rec->t = root;
	ray_at(ray, rec->t, &rec->point);
	v_copy(&rec->normal, &plane->normal);
	rec->color = plane->color;
}

int	hit_plane(t_object *plane, const t_ray *ray, t_hit_record *rec)
{
	double	ray_tmin = 0.001;
	double	ray_tmax = INF;
	t_vector3	origin_to_point;
	double	root;

	v_sub(v_copy(&origin_to_point, &plane->point), &ray->origin);
	root = v_dot(&origin_to_point, &plane->normal) \
			/ v_dot(&ray->direction, &plane->normal);
	if (root <= ray_tmin || ray_tmax <= root)
		return (0);
	save_to_record(rec, root, ray, plane);
	return (1);
}
