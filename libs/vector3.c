/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:13 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/07 17:22:22 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/vector3.h"

void	v_put(const t_vector3 *dest, const char *var_name)
{
	printf("%s(%lf, %lf, %lf)\n", var_name, dest->x, dest->y, dest->z);
}

t_vector3	v_create(t_decimal x, t_decimal y, t_decimal z)
{
	return ((t_vector3) {x, y, z});
}

t_vector3	*v_set(t_vector3 *dest, t_decimal x, t_decimal y, t_decimal z)
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

t_decimal	v_dot(const t_vector3 *dest, const t_vector3 *src)
{
	t_decimal	value;

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

t_vector3	*v_scalar_mul(t_vector3 *dest, t_decimal scalar)
{
	dest->x *= scalar;
	dest->y *= scalar;
	dest->z *= scalar;
	return (dest);
}

t_vector3	*v_cross(t_vector3 *dest, const t_vector3 *src)
{
	t_decimal	new_x;
	t_decimal	new_y;
	t_decimal	new_z;

	new_x = dest->y * src->z - dest->z * src->y;
	new_y = dest->z * src->x - dest->x * src->z;
	new_z = dest->x * src->y - dest->y * src->x;
	dest->x = new_x;
	dest->y = new_y;
	dest->z = new_z;
	return (dest);
}

t_decimal	v_norm2(const t_vector3 *dest)
{
	t_decimal	norm2;

	norm2 = v_dot(dest, dest);
	return (norm2);
}

t_decimal	v_norm(const t_vector3 *dest)
{
	t_decimal	norm2;
	t_decimal	norm;

	norm2 = v_norm2(dest);
	norm = sqrt(norm2);
	return (norm);
}

// can cause error if dest's norm is 0
t_vector3	*v_normalize(t_vector3 *dest)
{
	t_decimal	norm;

	norm = v_norm(dest);
	v_scalar_mul(dest, 1.0f / norm);
	return (dest);
}
