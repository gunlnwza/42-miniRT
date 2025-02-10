#include "../../includes/object.h"

t_object	*create_sphere(const t_vector3 *center, t_decimal radius, int color)
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


// return bool
int hit_sphere(t_object *sphere, const t_ray *ray, t_hit_record *rec)
{
	t_decimal ray_tmin = 0.001;
	t_decimal ray_tmax = INF;

	t_vector3	oc;  // = C - O  (center - ray_origin)
	v_copy(&oc, &sphere->point);
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
	v_sub(&rec->normal, &sphere->point);
	v_normalize(&rec->normal);
	rec->color = sphere->color;
	return (1);
}
