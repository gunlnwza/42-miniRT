/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:44:17 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 00:33:57 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	parse_scene(int number_of_lines, char ***file_tokens, t_world *w)
{
	int				i;
	char			**line;
	t_scene_type	type;

	i = 0;
	while (i < number_of_lines)
	{
		line = file_tokens[i];
		type = identify_scene_type(line[0]);
		if ((type == SCENE_AMBIENT && parse_ambient(line, w) != SUCCESS)
			|| (type == SCENE_CAMERA && parse_camera(line, w) != SUCCESS)
			|| (type == SCENE_LIGHT && parse_light(line, w) != SUCCESS)
			|| (type == SCENE_SPHERE && parse_sphere(line, w) != SUCCESS)
			|| (type == SCENE_PLANE && parse_plane(line, w) != SUCCESS)
			|| (type == SCENE_CYLINDER && parse_cylinder(line, w) != SUCCESS)
			|| (type == SCENE_INVALID))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
