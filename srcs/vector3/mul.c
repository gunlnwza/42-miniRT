/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mul.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:07:36 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:07:36 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector3.h"

t_vector3	*v_element_mul(t_vector3 *dest, const t_vector3 *src)
{
	dest->x *= src->x;
	dest->y *= src->y;
	dest->z *= src->z;
	return (dest);
}

t_vector3	*v_scalar_mul(t_vector3 *dest, double scalar)
{
	dest->x *= scalar;
	dest->y *= scalar;
	dest->z *= scalar;
	return (dest);
}
