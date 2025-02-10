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
