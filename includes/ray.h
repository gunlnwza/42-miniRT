/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:20 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/25 16:45:28 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vector3.h"

# define RAY_T_MIN 0.001
# define RAY_T_MAX 4200000

typedef struct s_ray
{
	t_vector3	origin;
	t_vector3	direction;
}	t_ray;

t_vector3	ray_at(const t_ray *ray, double t);

#endif
