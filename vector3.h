/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:15 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 14:29:19 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include <stdlib.h>
# include <math.h>

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

void		vector3_put(const t_vector3 *dest, const char *var_name);

void		vector3_set_values_ip(t_vector3 *dest, float x, float y, float z);
t_vector3	*vector3_create(float x, float y, float z);
void		vector3_copy_ip(t_vector3 *dest, const t_vector3 *src);
t_vector3	*vector3_copy(const t_vector3 *src);

void		vector3_add_ip(t_vector3 *dest, const t_vector3 *src);
t_vector3	*vector3_add(t_vector3 *dest, const t_vector3 *src);

void		vector3_sub_ip(t_vector3 *dest, const t_vector3 *src);
t_vector3	*vector3_sub(t_vector3 *dest, const t_vector3 *src);

float		vector3_dot(const t_vector3 *dest, const t_vector3 *src);

void		vector3_element_mul_ip(t_vector3 *dest, const t_vector3 *src);
t_vector3	*vector3_element_mul(t_vector3 *dest, const t_vector3 *src);

void		vector3_scalar_mul_ip(t_vector3 *dest, float scalar);
t_vector3	*vector3_scalar_mul(t_vector3 *dest, float scalar);

void		vector3_cross_ip(t_vector3 *dest, const t_vector3 *src);
t_vector3	*vector3_cross(t_vector3 *dest, const t_vector3 *src);

float		vector3_norm2(const t_vector3 *dest);
float		vector3_norm(const t_vector3 *dest);

void		vector3_normalize_ip(t_vector3 *dest);
t_vector3	*vector3_normalize(const t_vector3 *dest);

void		vector3_free(t_vector3 **dest);

#endif
