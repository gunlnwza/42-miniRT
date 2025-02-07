#include "sphere.h"

t_sphere	*create_sphere(const t_vector3 *center, t_decimal radius, int color)
{
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (NULL);	
	v_copy(&sphere->center, center);
	sphere->radius = radius;
	sphere->color = color;
	return (sphere);
}

// return bool
int hit_sphere(t_sphere *sphere, const t_ray *ray, t_decimal ray_tmin, t_decimal ray_tmax, t_hit_record *rec)
{
	t_vector3	oc;
	v_copy(&oc, &sphere->center);
	v_sub(&oc, &ray->origin);

	t_decimal a = v_norm2(&ray->direction);
	t_decimal h = v_dot(&ray->direction, &oc);
	t_decimal c = v_norm2(&oc) - (sphere->radius * sphere->radius);
	
	t_decimal discriminant = h * h - a * c;
	if (discriminant < 0)
		return (0);

	t_decimal sqrtd = sqrtf(discriminant);

	t_decimal root = (h - sqrtd) / a;
	if (root <= ray_tmin || ray_tmax <= root)
	{
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || ray_tmax <= root)
			return (0);
	}

	// save to record
	rec->t = root;

	ray_at(ray, rec->t, &rec->point);

	v_copy(&rec->normal, &rec->point);
	v_sub(&rec->normal, &sphere->center);
	v_normalize(&rec->normal);

	rec->color = sphere->color;

	return (1);
}
