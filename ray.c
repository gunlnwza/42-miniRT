/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:24 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 14:19:44 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

void	ray_at(const t_ray *ray, float t, t_vector3 *res_point)
{
	t_vector3	dir;

	v_copy(res_point, &ray->origin);
	v_copy(&dir, &ray->direction);
	v_add(res_point, v_scalar_mul(&dir, t));
}
