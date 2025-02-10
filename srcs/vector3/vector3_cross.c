/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:05:40 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:07:22 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector3.h"

t_vector3	*v_cross(t_vector3 *dest, const t_vector3 *src)
{
	double	new_x;
	double	new_y;
	double	new_z;

	new_x = dest->y * src->z - dest->z * src->y;
	new_y = dest->z * src->x - dest->x * src->z;
	new_z = dest->x * src->y - dest->y * src->x;
	v_set(dest, new_x, new_y, new_z);
	return (dest);
}
