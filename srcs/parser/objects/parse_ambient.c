/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:49 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 00:30:23 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

t_parse_result	validate_ambient(char **line)
{
	t_parse_result	ret;

	ret = PARSE_OK;
	if (array_length(line) != 3)
		ret = BAD_NUMBER_OF_PARAMS;
	if (!is_valid_ratio(line[1]))
		ret = BAD_RATIO;
	if (!is_valid_color(line[2]))
		ret = BAD_COLOR;
	return (ret);
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
