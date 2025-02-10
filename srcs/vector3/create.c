/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:04:08 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:05:33 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector3.h"

t_vector3	*v_set(t_vector3 *dest, double x, double y, double z)
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


t_vector3	v_create(double x, double y, double z)
{
	return ((t_vector3) {x, y, z});
}

t_vector3	v_copy_create(const t_vector3 *src)
{
	return (v_create(src->x, src->y, src->z));
}
