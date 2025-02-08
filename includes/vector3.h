/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:15 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/07 17:22:48 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include <stdlib.h>
# include <math.h>
# include "constants.h"
# include "utils.h"

typedef struct s_vector3
{
	t_decimal	x;
	t_decimal	y;
	t_decimal	z;
}	t_vector3;

// vector3 lib: short func name, encourage stack alloc, modify inplace, will return ptr to dest;

void		v_put(const t_vector3 *dest, const char *var_name);
t_vector3	v_create(t_decimal x, t_decimal y, t_decimal z);
t_vector3	*v_set(t_vector3 *dest, t_decimal x, t_decimal y, t_decimal z);
t_vector3	*v_copy(t_vector3 *dest, const t_vector3 *src);
t_vector3	*v_add(t_vector3 *dest, const t_vector3 *src);
t_vector3	*v_sub(t_vector3 *dest, const t_vector3 *src);

t_decimal		v_dot(const t_vector3 *dest, const t_vector3 *src);

t_vector3	*v_element_mul(t_vector3 *dest, const t_vector3 *src);
t_vector3	*v_scalar_mul(t_vector3 *dest, t_decimal scalar);
t_vector3	*v_cross(t_vector3 *dest, const t_vector3 *src);

t_decimal		v_norm2(const t_vector3 *dest);
t_decimal		v_norm(const t_vector3 *dest);

t_vector3	*v_normalize(t_vector3 *dest);

#endif
