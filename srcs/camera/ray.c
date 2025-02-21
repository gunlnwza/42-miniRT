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
t_vector3	ray_at(const t_ray *ray, double t)
{
	t_vector3	diff;

	diff = v_copy(&ray->direction);
	v_scalar_mul_ip(&diff, t);
	return (v_add(&ray->origin, &diff));
}
