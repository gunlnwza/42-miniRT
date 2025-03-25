/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:53 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 16:11:03 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_parse_result	validate_camera(char **line)
{
	t_parse_result	ret;

	ret = PARSE_OK;
	if (array_length(line) != 4)
		ret = BAD_NUMBER_OF_PARAMS;
	if (!is_valid_pos(line[1]))
		ret = BAD_POSITION;
	if (!is_valid_normal(line[2]))
		ret = BAD_NORMAL;
	if (!is_valid_fov(line[3]))
		ret = BAD_FOV;
	return (ret);
}

int	parse_camera(char **line, t_world *world)
{
	int	ret;

	ret = parse_vector(line[1], &world->camera.center);
	if (ret < 0)
		return (ERROR);
	ret = parse_normal_vector(line[2], &world->camera.normal);
	if (ret < 0)
		return (ERROR);
	world->camera.deg_fov = parse_fov(line[3]);
	return (SUCCESS);
}
