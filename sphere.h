/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:20 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 15:39:32 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "ray.h"

typedef struct s_hit_record
{
	t_vector3	point;
	t_vector3	normal;
	float		t;
}	t_hit_record;

typedef struct s_sphere
{
	t_vector3	center;
	float		radius;
}	t_sphere;

int hit_sphere(t_sphere *sphere, const t_ray *ray, float ray_tmin, float ray_tmax, t_hit_record *rec);

#endif
