/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:15:25 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:25:42 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vector3.h"

// can cause error if dest's norm is 0
t_vector3	*v_normalize(t_vector3 *dest)
{
	v_scalar_mul(dest, 1.0f / v_norm(dest));
	return (dest);
}
