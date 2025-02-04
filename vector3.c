#include "vector3.h"

t_vector3	*vector3_create(float x, float y, float z)
{
	t_vector3	*u;

	u = malloc(sizeof(t_vector3));
	if (u == NULL)
		return (NULL);
	u->x = x;
	u->y = y;
	u->z = z;
	return (u);
}

void	vector3_add_ip(t_vector3 *dest, t_vector3 *src)
{
	dest->x += src->x;
	dest->y += src->y;
	dest->z += src->z;
}

void	vector3_sub_ip(t_vector3 *dest, t_vector3 *src)
{
	dest->x -= src->x;
	dest->y -= src->y;
	dest->z -= src->z;
}

float	vector3_dot(t_vector3 *dest, t_vector3 *src)
{
	float	value;

	value = (dest->x * src->x) + (dest->y * src->y) + (dest->z * src->z);
	return (value);
}

// multiply element-wise
void	vector3_element_mul_ip(t_vector3 *dest, t_vector3 *src)
{
	dest->x *= src->x;
	dest->y *= src->y;
	dest->z *= src->z;
}

void	vector3_scalar_mul_ip(t_vector3 *dest, float scalar)
{
	dest->x *= scalar;
	dest->y *= scalar;
	dest->z *= scalar;
}

void	vector3_cross_ip(t_vector3 *dest, t_vector3 *src)
{
	float	x;
	float	y;
	float	z;

	x = dest->y * src->z - dest->z * src->y;
	y = dest->z * src->x - dest->x * src->z;
	z = dest->x * src->y - dest->y * src->x;
	dest->x = x;
	dest->y = y;
	dest->z = z;
}

float	vector3_norm2(t_vector3 *dest)
{
	float	norm2;

	norm2 = vector3_dot(dest, dest);
	return (norm2);
}

float	vector3_norm(t_vector3 *dest)
{
	float	norm2;
	float	norm;

	norm2 = vector3_norm2(dest);
	norm = sqrtf(norm2);
	return (norm);
}

// can cause error if dest's norm is 0
void	vector3_normalize_ip(t_vector3 *dest)
{
	float	norm;

	norm = vector3_norm(dest);
	vector3_scalar_mul_ip(dest, 1 / norm);
}

void	vector3_free(t_vector3 **dest)
{
	free(*dest);
	*dest = NULL;
}
