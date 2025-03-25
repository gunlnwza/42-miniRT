/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:49 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:30:50 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	validate_ambient(char **line)
{
	if (array_length(line) != 3)
	{
		ft_putendl_fd("Invalid ambient parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_ratio(line[1]))
	{
		ft_putendl_fd("Invalid ambient brightness", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[2]))
	{
		ft_putendl_fd("Invalid ambient color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_ambient(char **line, t_world *world)
{
	int		color;
	double	ratio;

	ratio = parse_ratio(line[1]);
	if (parse_color(line[2], &color) < 0)
		return (ERROR);
	world->ambient_light_color = scale_color(color, ratio);
	return (SUCCESS);
}
