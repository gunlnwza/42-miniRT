/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:32:43 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	validate_light(char **line)
{
	if (array_length(line) != 4)
	{
		ft_putendl_fd("Invalid light parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_pos(line[1]))
	{
		ft_putendl_fd("Invalid light position", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_ratio(line[2]))
	{
		ft_putendl_fd("Invalid light brightness", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[3]))
	{
		ft_putendl_fd("Invalid light color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_light(char **line, t_world *world)
{
	int		ret;
	int		color;
	double	ratio;

	ret = parse_vector(line[1], &world->light.point);
	if (ret != SUCCESS)
		return (ERROR);
	ratio = parse_ratio(line[2]);
	if (parse_color(line[3], &color) != SUCCESS)
		return (ERROR);
	world->light.color = scale_color(color, ratio);
	return (SUCCESS);
}
