/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:45 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/02/25 17:46:45 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

static int	is_valid_number(const char *str)
{
	if (*str == '\0') // Check for empty string
		return (0);
	if (*str == '-' || *str == '+') // Check for sign
		str++;
	while (*str)
	{
		printf ("asshole");
		if (!ft_isdigit(*str)) // Check if each character is a digit
			return (0);
		str++;
	}
	return (1);
}

int	parse_vector(char *str, t_vector3 *vect)
{
	char	**nbrs;
	int		i;

	nbrs = ft_split(str, ',');
	if (array_length(nbrs) != 3)
	{
		free_array(nbrs);
		return (1);
	}
	i = 0;
	while (!is_valid_number(nbrs[i]))
	{
		free_array(nbrs);
		return(1);
	}
	vect->x = ft_atof(nbrs[0]);
	vect->y = ft_atof(nbrs[1]);
	vect->z = ft_atof(nbrs[2]);
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
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	*color = get_rgba(r, g, b, 255);
	free_array(rgb);
	return (0);
}

int	parse_double(char *str, double *num)
{
	char	*endptr;

	*num = ft_strtod(str, &endptr);
	if (*endptr == '\0')
		return (0);
	return (1);
}

int	ft_sscanf(const char *str, int *r, int *g, int *b)
{
	int		count;
	char	*endptr;

	count = 0;
	*r = (int)ft_strtol(str, &endptr);
	if (*r < 0 || *r > 255)
		return (count);
	count++;
	if (*endptr == ',')
		endptr++;
	if (*endptr != ',')
	{
		*g = (int)ft_strtol(endptr, &endptr);
		if (*g < 0 || *g > 255)
			return (count);
		count++;
	}
	if (*endptr == ',')
		endptr++;
	*b = (int)ft_strtol(endptr, &endptr);
	if (*b < 0 || *b > 255)
		return (count);
	count++;
	return (count);
}
