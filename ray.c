/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:24 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/07 17:19:02 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	ray_at(const t_ray *ray, t_decimal t, t_vector3 *res_point)
{
	t_vector3	direction;

	v_copy(&direction, &ray->direction);
	v_copy(res_point, &ray->origin);
	v_add(res_point, v_scalar_mul(&direction, t));
}
