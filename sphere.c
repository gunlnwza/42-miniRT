#include "sphere.h"

// return bool
int hit_sphere(t_sphere *sphere, const t_ray *ray, float ray_tmin, float ray_tmax, t_hit_record *rec)
{
	t_vector3	oc;
	vector3_copy_ip(&oc, &sphere->center);
	vector3_sub_ip(&oc, &ray->origin);

	float a = vector3_norm2(&ray->direction);
	float h = vector3_dot(&ray->direction, &oc);
	float c = vector3_norm2(&oc) - sphere->radius * sphere->radius;
	
	float discriminant = h*h - a*c;
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
	
	vector3_copy_ip(&rec->normal, &rec->point);
	vector3_sub_ip(&rec->normal, &sphere->center);
	vector3_normalize_ip(&rec->normal);

	return (1);
}
