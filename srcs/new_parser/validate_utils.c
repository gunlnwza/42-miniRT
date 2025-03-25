/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:42:59 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:22:45 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_in_range(int min, int max, int x)
{
	return (min <= x && x <= max);
}

int	is_in_rangef(double min, double max, double x)
{
	return (min <= x && x <= max);
}

int	is_same_after_ft_atoi(const char *nptr)
{
	int		value;
	char	*after;
	int		ret;

	value = ft_atoi(nptr);
	after = ft_itoa(value);
	if (after == NULL)
		return (FALSE);
	ret = ft_strcmp(nptr, after);
	free(after);
	return (ret == 0);
}

int	is_valid_ratio(char *ratio)
{
	double	value;
	char	*endptr;

	value = ft_strtod(ratio, &endptr);
	if (*endptr != '\0')
		return (FALSE);
	if (!is_in_rangef(0, 1, value))
		return (FALSE);
	return (TRUE);
}

int	is_valid_color(char *rgb_str)
{
	char	**rgb;
	int		value;
	char	*endptr;
	int		i;

	rgb = ft_split(rgb_str, ',');
	if (rgb == NULL)
		return (FALSE);
	if (array_length(rgb) != 3)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		value = ft_strtol(rgb[i], &endptr);
		if (*endptr != '\0' || !is_in_range(0, 255, value))
			return (FALSE);
		i++;
	}
	free_array(rgb);
	return (TRUE);
}

int	is_valid_pos(char *pos_str)
{
	double	value;
	char	*endptr;
	char	**xyz;
	int		i;

	xyz = ft_split(pos_str, ',');
	if (xyz == NULL)
		return (FALSE);
	if (array_length(xyz) != 3)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		value = ft_strtod(xyz[i], &endptr);
		if (*endptr != '\0')
			return (FALSE);
		i++;
	}
	(void) value;
	return (TRUE);
}

int	is_valid_normal(char *normal_str)
{
	double	value;
	char	*endptr;
	char	**xyz;
	int		i;

	xyz = ft_split(normal_str, ',');
	if (xyz == NULL)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		value = ft_strtod(xyz[i], &endptr);
		if (*endptr != '\0' || !is_in_rangef(-1, 1, value))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_valid_length(char *length_str)
{
	double	value;
	char	*endptr;

	value = ft_strtod(length_str, &endptr);
	if (*endptr != '\0' || value <= 0)
		return (FALSE);
	return (TRUE);
}

int	is_valid_fov(char *fov_str)
{
	int		value;
	char	*endptr;

	value = ft_strtol(fov_str, &endptr);
	if (*endptr != '\0' || !is_in_rangef(0, 180, value))
		return (FALSE);
	return (TRUE);
}
