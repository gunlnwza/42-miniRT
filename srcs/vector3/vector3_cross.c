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

t_vector3	v_cross(const t_vector3 *a, const t_vector3 *b)
{
	return ((t_vector3) {
		(a->y * b->z) - (a->z * b->y),
		(a->z * b->x) - (a->x * b->z),
		(a->x * b->y) - (a->y * b->x)
	});
}
