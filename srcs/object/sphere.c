#include "../../includes/object.h"

t_object	*create_sphere(const t_vector3 *center, double radius, int color)
{
	t_object	*sphere;

	sphere = malloc(sizeof(t_object));
	if (sphere == NULL)
		return (NULL);
	sphere->type = SPHERE;
	v_copy(&sphere->point, center);
	sphere->color = color;
	sphere->radius = radius;
	return (sphere);
}

static void	save_to_record(t_hit_record *rec, double root,
				const t_ray *ray, t_object *sphere)
{
	rec->t = root;
	\
	ray_at(ray, rec->t, &rec->point);
	\
	v_sub(v_copy(&rec->normal, &rec->point), &sphere->point);
	v_normalize(&rec->normal);
	\
	rec->color = sphere->color;
}

// return bool
int hit_sphere(t_object *sphere, const t_ray *ray, t_hit_record *rec)
{
	double ray_tmin = 0.001;
	double ray_tmax = INF;

	t_vector3	oc;  // = C - O  (center - ray_origin)
	v_copy(&oc, &sphere->point);
	v_sub(&oc, &ray->origin);

	double a = v_norm2(&ray->direction);
	double h = v_dot(&ray->direction, &oc);
	double c = v_norm2(&oc) - (sphere->radius * sphere->radius);
	
	double discriminant = h * h - a * c;
	if (discriminant < 0)
		return (0);

	double sqrtd = sqrtf(discriminant);

	double root = (h - sqrtd) / a;
	if (root <= ray_tmin || ray_tmax <= root)
	{
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root)
			return (0);
	}
	save_to_record(rec, root, ray, sphere);
	return (1);
}
