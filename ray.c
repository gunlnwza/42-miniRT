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
	t_vector3	diff;

	diff = ray->direction;
	vector3_scalar_mul_ip(&diff, t);
	vector3_copy_ip(res_point, &ray->origin);
	vector3_add_ip(res_point, &diff);
}
