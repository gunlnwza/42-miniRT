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

#include "../../includes/ray.h"

// will move into camera dir later
void	ray_at(const t_ray *ray, double t, t_vector3 *res_point)
{
	t_vector3	diff;

	v_scalar_mul_ip(v_copy_ip(&diff, &ray->direction), t);
	v_copy_ip(res_point, &ray->origin);
	v_add_ip(res_point, &diff);
}
