/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:59:20 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/07 17:19:59 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "ray.h"
# include "hit_record.h"

typedef struct s_sphere
{
	t_vector3	center;
	t_decimal		radius;
	int			color;
}	t_sphere;

t_sphere	*create_sphere(const t_vector3 *center, t_decimal radius, int color);
int			hit_sphere(t_sphere *sphere, const t_ray *ray, t_decimal ray_tmin, t_decimal ray_tmax, t_hit_record *rec);

#endif
