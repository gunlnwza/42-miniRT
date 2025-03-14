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

int	is_valid_number(const char *str)
{
	if (*str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
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
	while (i < 3)
	{
		if (!is_valid_double(nbrs[i]))
		{
			free_array(nbrs);
			return (1);
		}
		i++;
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
	int		i;

	rgb = ft_split(str, ',');
	if (array_length(rgb) != 3)
	{
		free_array(rgb);
		return (1);
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_number(rgb[i]))
		{
			free_array(rgb);
			return (1);
		}
		i++;
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_array(rgb);
		return (1);
	}
	*color = get_rgba(r, g, b, 255);
	free_array(rgb);
	return (0);
}

int	parse_double(char *str, double *num)
{
	char	*endptr;

	*num = ft_strtod(str, &endptr);
	if (*endptr == '\0' && *num > 0)
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
