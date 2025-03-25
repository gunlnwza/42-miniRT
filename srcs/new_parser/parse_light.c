/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 16:11:22 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_parse_result	validate_light(char **line)
{
	t_parse_result	ret;

	ret = PARSE_OK;
	if (array_length(line) != 4)
		ret = BAD_NUMBER_OF_PARAMS;
	if (!is_valid_pos(line[1]))
		ret = BAD_POSITION;
	if (!is_valid_ratio(line[2]))
		ret = BAD_RATIO;
	if (!is_valid_color(line[3]))
		ret = BAD_COLOR;
	return (ret);
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
