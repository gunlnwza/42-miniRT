/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:24 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 18:11:23 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ray.h"

void	ray_at(const t_ray *ray, double t, t_vector3 *res_point)
{
	t_vector3	diff;

	v_scalar_mul(v_copy(&diff, &ray->direction), t);
	v_copy(res_point, &ray->origin);
	v_add(res_point, &diff);
}
