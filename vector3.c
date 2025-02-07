/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:13 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/07 14:56:43 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "vector3.h"

void	v_put(const t_vector3 *dest, const char *var_name)
{
	printf("%s(%f, %f, %f)\n", var_name, dest->x, dest->y, dest->z);
}

t_vector3	*v_set(t_vector3 *dest, float x, float y, float z)
{
	dest->x = x;
	dest->y = y;
	dest->z = z;
	return (dest);
}

t_vector3	*v_copy(t_vector3 *dest, const t_vector3 *src)
{
	dest->x = src->x;
	dest->y = src->y;
	dest->z = src->z;
	return (dest);
}

t_vector3	*v_add(t_vector3 *dest, const t_vector3 *src)
{
	dest->x += src->x;
	dest->y += src->y;
	dest->z += src->z;
	return (dest);
}

t_vector3	*v_sub(t_vector3 *dest, const t_vector3 *src)
{
	dest->x -= src->x;
	dest->y -= src->y;
	dest->z -= src->z;
	return (dest);
}

float	v_dot(const t_vector3 *dest, const t_vector3 *src)
{
	float	value;

	value = (dest->x * src->x) + (dest->y * src->y) + (dest->z * src->z);
	return (value);
}

t_vector3	*v_element_mul(t_vector3 *dest, const t_vector3 *src)
{
	dest->x *= src->x;
	dest->y *= src->y;
	dest->z *= src->z;
	return (dest);
}

t_vector3	*v_scalar_mul(t_vector3 *dest, float scalar)
{
	dest->x *= scalar;
	dest->y *= scalar;
	dest->z *= scalar;
	return (dest);
}

t_vector3	*v_cross(t_vector3 *dest, const t_vector3 *src)
{
	float	new_x;
	float	new_y;
	float	new_z;

	new_x = dest->y * src->z - dest->z * src->y;
	new_y = dest->z * src->x - dest->x * src->z;
	new_z = dest->x * src->y - dest->y * src->x;
	dest->x = new_x;
	dest->y = new_y;
	dest->z = new_z;
	return (dest);
}

float	v_norm2(const t_vector3 *dest)
{
	float	norm2;

	norm2 = v_dot(dest, dest);
	return (norm2);
}

float	v_norm(const t_vector3 *dest)
{
	float	norm2;
	float	norm;

	norm2 = v_norm2(dest);
	norm = sqrtf(norm2);
	return (norm);
}

// can cause error if dest's norm is 0
t_vector3	*v_normalize(t_vector3 *dest)
{
	float	norm;

	norm = v_norm(dest);
	v_scalar_mul(dest, 1.0f / norm);
	return (dest);
}
