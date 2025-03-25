/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:55 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:32:24 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	validate_cylinder(char **line)
{
	if (array_length(line) != 6)
	{
		ft_putendl_fd("Invalid cylinder parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_pos(line[1]))
	{
		ft_putendl_fd("Invalid cylinder position", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_normal(line[2]))
	{
		ft_putendl_fd("Invalid cylinder normal vector", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_length(line[3]))
	{
		ft_putendl_fd("Invalid cylinder diameter", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_length(line[4]))
	{
		ft_putendl_fd("Invalid cylinder height", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[5]))
	{
		ft_putendl_fd("Invalid cylinder color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	parse_cylinder(char **line, t_world *world)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		return (ERROR);
	object->type = CYLINDER;
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
	object->radius = ft_atof(line[3]) / 2;
	object->height = ft_atof(line[4]);
	if (parse_color(line[5], &object->color) < 0)
	{
		free(object);
		return (ERROR);
	}
	world->objects[world->nb_objects++] = object;
	return (SUCCESS);
}
