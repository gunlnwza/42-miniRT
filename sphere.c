#include "sphere.h"

// return bool
int hit_sphere(t_sphere *sphere, const t_ray *ray, float ray_tmin, float ray_tmax, t_hit_record *rec)
{
	t_vector3	oc;
	v_copy(&oc, &sphere->center);
	v_sub(&oc, &ray->origin);

	float a = v_norm2(&ray->direction);
	float h = v_dot(&ray->direction, &oc);
	float c = v_norm2(&oc) - (sphere->radius * sphere->radius);
	
	float discriminant = h * h - a * c;
	if (discriminant < 0)
		return (0);

	float sqrtd = sqrtf(discriminant);

	float root = (h - sqrtd) / a;
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

	return (1);
}
