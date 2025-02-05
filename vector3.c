/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:13 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 11:32:24 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

void	vector3_set_values(t_vector3 *src, float x, float y, float z)
{
	src->x = x;
	src->y = y;
	src->z = z;
}

t_vector3	*vector3_create(float x, float y, float z)
{
	t_vector3	*u;

	u = malloc(sizeof(t_vector3));
	if (u == NULL)
		return (NULL);
	vector3_set_values(u, x, y, z);
	return (u);
}

t_vector3	*vector3_copy(const t_vector3 *src)
{
	t_vector3	*dest;

	dest = vector3_create(src->x, src->y, src->z);
	if (dest == NULL)
		return (NULL);
	return (dest);
}

t_vector3	*vector3_operation(t_vector3 *dest, t_vector3 *src, void (*inplace_func)(t_vector3*, t_vector3*))
{
	t_vector3	*new;

	new = vector3_copy(dest);
	if (new == NULL)
		return (NULL);
	inplace_func(new, src);
	return (new);
}

void	vector3_add_ip(t_vector3 *dest, t_vector3 *src)
{
	dest->x += src->x;
	dest->y += src->y;
	dest->z += src->z;
}

t_vector3	*vector3_add(t_vector3 *dest, t_vector3 *src)
{
	return (vector3_operation(dest, src, vector3_add_ip));
}

void	vector3_sub_ip(t_vector3 *dest, t_vector3 *src)
{
	dest->x -= src->x;
	dest->y -= src->y;
	dest->z -= src->z;
}

t_vector3	*vector3_sub(t_vector3 *dest, t_vector3 *src)
{
	return (vector3_operation(dest, src, vector3_sub_ip));
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

t_vector3	*vector3_element_mul(t_vector3 *dest, t_vector3 *src)
{
	return (vector3_operation(dest, src, vector3_element_mul_ip));
}

void	vector3_scalar_mul_ip(t_vector3 *dest, float scalar)
{
	dest->x *= scalar;
	dest->y *= scalar;
	dest->z *= scalar;
}

t_vector3	*vector3_scalar_mul(t_vector3 *dest, float scalar)
{
	t_vector3	*new;

	new = vector3_copy(dest);
	if (new == NULL)
		return (NULL);
	vector3_scalar_mul_ip(new, scalar);
	return (new);
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

t_vector3	*vector3_cross(t_vector3 *dest, t_vector3 *src)
{
	return (vector3_operation(dest, src, vector3_cross_ip));
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
	vector3_scalar_mul_ip(dest, 1.0f / norm);
}

t_vector3	*vector3_normalize(t_vector3 *dest)
{
	t_vector3	*new;

	new = vector3_copy(dest);
	if (new == NULL)
		return (NULL);
	vector3_normalize_ip(new);
	return (new);
}

void	vector3_free(t_vector3 **dest)
{
	free(*dest);
	*dest = NULL;
}
