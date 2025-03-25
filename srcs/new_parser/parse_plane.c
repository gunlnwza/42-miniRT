/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:31:04 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:32:59 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	validate_plane(char **line)
{
	if (array_length(line) != 4)
	{
		ft_putendl_fd("Invalid plane parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_pos(line[1]))
	{
		ft_putendl_fd("Invalid plane position", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_normal(line[2]))
	{
		ft_putendl_fd("Invalid plane normal vector", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[3]))
	{
		ft_putendl_fd("Invalid plane color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_plane(char **line, t_world *world)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		return (ERROR);
	object->type = PLANE;
	if (parse_vector(line[1], &object->point) < 0)
	{
		free(object);
		return (ERROR);
	}
	if (parse_normal_vector(line[2], &object->normal) < 0)
	{
		free(object);
		return (ERROR);
	}
	if (parse_color(line[3], &object->color) < 0)
	{
		free(object);
		return (ERROR);
	}
	world->objects[world->nb_objects++] = object;
	return (SUCCESS);
}
