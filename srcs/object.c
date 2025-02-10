#include "../includes/object.h"
#include <stdio.h>

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

t_object    *create_cylinder(const t_vector3 *point, t_decimal radius, const t_vector3 *normal, int color, t_decimal height)
{
	t_object	*cylinder;

	cylinder = malloc(sizeof(t_object));
	if (cylinder == NULL)
		return (NULL);
	cylinder->type = CYLINDER;
	v_copy(&cylinder->point, point);
	cylinder->radius = radius;
	v_copy(&cylinder->normal, normal);
	cylinder->color = color;
	cylinder->height = height;
	return (cylinder);
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

int	hit_cylinder(t_object *cylinder, const t_ray *ray, t_hit_record *rec)
{
	t_decimal ray_tmin = 0.001;
	t_decimal ray_tmax = INF;

	t_vector3	center_to_origin;
	v_copy(&center_to_origin, &ray->origin);
	v_sub(&center_to_origin, &cylinder->point);

	t_vector3	A;
	v_copy(&A, &center_to_origin);

	t_vector3 temp_normal;
	v_copy(&temp_normal, &cylinder->normal);
	v_scalar_mul(&temp_normal, v_dot(&A, &cylinder->normal));

	t_vector3	A_perpen;
	v_copy(&A_perpen, &A);
	v_sub(&A_perpen, &temp_normal);


	t_vector3	D;
	v_copy(&D, &ray->direction);

	v_copy(&temp_normal, &cylinder->normal);
	v_scalar_mul(&temp_normal, v_dot(&D, &cylinder->normal));

	t_vector3	D_perpen;
	v_copy(&D_perpen, &D);
	v_sub(&D_perpen, &temp_normal);


	t_decimal a, b, c;

	a = v_norm2(&D_perpen);
	b = 2 * v_dot(&A_perpen, &D_perpen);
	c = v_norm2(&A_perpen) - (cylinder->radius * cylinder->radius);
	
	t_decimal discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);

	t_decimal sqrtd = sqrtf(discriminant);

	t_decimal root = (-b - sqrtd) / (2*a);
	if (root <= ray_tmin || ray_tmax <= root)
	{
		root = (-b + sqrtd) / (2*a);
		if (root <= ray_tmin || ray_tmax <= root)
			return (0);
	}

	// save to record
	rec->t = root;

	ray_at(ray, rec->t, &rec->point);

	t_vector3	CP;
	v_copy(&CP, &rec->point);
	v_sub(&CP, &cylinder->point);

	v_copy(&temp_normal, &cylinder->normal);
	v_scalar_mul(&temp_normal, v_dot(&CP, &cylinder->normal));

	t_vector3 n;
	v_copy(&n, &CP);
	v_sub(&n, &temp_normal);

	v_copy(&rec->normal, &n);
	v_normalize(&rec->normal);
	
	rec->color = cylinder->color;

	return (1);
}
