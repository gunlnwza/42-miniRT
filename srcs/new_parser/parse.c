/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:44:17 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 16:44:42 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static t_parse_result	validate_line(char **line, t_scene_type type)
{
	if (type == SCENE_AMBIENT)
		return (validate_ambient(line));
	else if (type == SCENE_CAMERA)
		return (validate_camera(line));
	else if (type == SCENE_LIGHT)
		return (validate_light(line));
	else if (type == SCENE_SPHERE)
		return (validate_sphere(line));
	else if (type == SCENE_PLANE)
		return (validate_plane(line));
	else if (type == SCENE_CYLINDER)
		return (validate_cylinder(line));
	else
		return (INVALID_OBJECT);
}

char	*get_object_str(t_scene_type type)
{
	if (type == SCENE_AMBIENT)
		return ("Ambient light");
	else if (type == SCENE_CAMERA)
		return ("Camera");
	else if (type == SCENE_LIGHT)
		return ("Light");
	else if (type == SCENE_SPHERE)
		return ("Sphere");
	else if (type == SCENE_PLANE)
		return ("Plane");
	else if (type == SCENE_CYLINDER)
		return ("Cylinder");
	return ("");
}

char	*get_issue_str(t_parse_result ret)
{
	if (ret == INVALID_OBJECT)
		return ("Invalid object id");
	else if (ret == MORE_THAN_ONE_OBJECT)
		return ("Unique object more than one");
	else if (ret == BAD_NUMBER_OF_PARAMS)
		return ("Invalid number of parameters");
	else if (ret == BAD_RATIO)
		return ("Invalid brightness");
	else if (ret == BAD_COLOR)
		return ("Invalid color format");
	else if (ret == BAD_POSITION)
		return ("Invalid position");
	else if (ret == BAD_NORMAL)
		return ("Invalid normal vector");
	else if (ret == BAD_FOV)
		return ("Invalid field of view");
	else if (ret == BAD_DIAMETER)
		return ("Invalid diameter");
	else if (ret == BAD_HEIGHT)
		return ("Invalid height");
	return ("");
}

void	print_error(t_parse_result ret, t_scene_type type)
{
	char	*object;
	char	*issue;

	object = get_object_str(type);
	issue = get_issue_str(ret);
	printf("Error\n");
	if (object)
		printf("%s: ", object);
	printf("%s\n", issue);
}

int	validate_scene(int number_of_lines, char ***file_tokens)
{
	int				i;
	char			**line;
	t_parse_result	ret;
	t_scene_type	type;

	i = 0;
	while (i < number_of_lines)
	{
		line = file_tokens[i];
		type = identify_scene_type(line[0]);
		ret = validate_line(line, type);
		if (ret != PARSE_OK)
		{
			print_error(ret, type);
			return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

int	parse_scene(int number_of_lines, char ***file_tokens, t_world *world)
{
	int				i;
	char			**line;
	t_scene_type	type;

	i = 0;
	while (i < number_of_lines)
	{
		line = file_tokens[i];
		type = identify_scene_type(line[0]);
		if ((type == SCENE_AMBIENT && parse_ambient(line, world) != SUCCESS)
			|| (type == SCENE_CAMERA && parse_camera(line, world) != SUCCESS)
			|| (type == SCENE_LIGHT && parse_light(line, world) != SUCCESS)
			|| (type == SCENE_SPHERE && parse_sphere(line, world) != SUCCESS)
			|| (type == SCENE_PLANE && parse_plane(line, world) != SUCCESS)
			|| (type == SCENE_CYLINDER && parse_cylinder(line, world) != SUCCESS)
			|| (type == SCENE_INVALID))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
