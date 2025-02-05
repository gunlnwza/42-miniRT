/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:20 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 14:19:39 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector3.h"

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

void	ray_at(const t_ray *ray, float t, t_vector3 *res_point);

#endif
