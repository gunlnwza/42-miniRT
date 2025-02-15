/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:04:04 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:09:11 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector3.h"

t_vector3	v_add(const t_vector3 *a, const t_vector3 *b)
{
	return (t_vector3){a->x + b->x, a->y + b->y, a->z + b->z};
}

t_vector3	*v_add_ip(t_vector3 *dest, const t_vector3 *src)
{
	dest->x += src->x;
	dest->y += src->y;
	dest->z += src->z;
	return (dest);
}

t_vector3	v_sub(const t_vector3 *a, const t_vector3 *b)
{
	return (t_vector3){a->x - b->x, a->y - b->y, a->z - b->z};
}

t_vector3	*v_sub_ip(t_vector3 *dest, const t_vector3 *src)
{
	dest->x -= src->x;
	dest->y -= src->y;
	dest->z -= src->z;
	return (dest);
}
