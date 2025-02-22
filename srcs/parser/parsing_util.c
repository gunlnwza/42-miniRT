/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:54:53 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/22 12:54:53 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

// receive vector_str and set the values of vect
int	parse_vector(char *str, t_vector3 *vect)
{
	char	**nbrs;

	nbrs = ft_split(str, ',');
	if (array_length(nbrs) != 3)
	{
		free_array(nbrs);
		return (1);
	}
	vect->x = atof(nbrs[0]);
	vect->y = atof(nbrs[1]);
	vect->z = atof(nbrs[2]);
	free_array(nbrs);
	return (0);
}

int	parse_color(char *str, int *color)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (array_length(rgb) != 3)
	{
		free_array(rgb);
		return (1);
	}
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	*color = get_rgba(r, g, b, 255);
	free_array(rgb);
	return (0);
}

int	parse_double(char *str, double *num)
{
	char	*endptr;

	*num = strtod(str, &endptr);
	if (*endptr == '\0')
		return (0);
	return (1);
}
