/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:04:01 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:07:31 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector3.h"

double	v_dot(const t_vector3 *dest, const t_vector3 *src)
{
	return ((dest->x * src->x) + (dest->y * src->y) + (dest->z * src->z));
}
