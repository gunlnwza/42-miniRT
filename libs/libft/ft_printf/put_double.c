/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 09:55:02 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 10:04:41 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	put_double(double x)
{
	unsigned int	len_put;
	unsigned int	len;

	len_put = 0;
	if (x < 0)
	{
		len_put += put_char('-');
		x *= -1;
	}
	len = put_int((int) x);
	len_put += len;
	len_put += put_char('.');
	\
	x = (x - (int) x) * 100;
	len = put_int((int) x);
	len_put += len;
	return (len_put);
}
