/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:30:53 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:31:26 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	validate_camera(char **line)
{
	if (array_length(line) != 4)
	{
		ft_putendl_fd("Invalid camera parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_pos(line[1]))
	{
		ft_putendl_fd("Invalid camera position", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_normal(line[2]))
	{
		ft_putendl_fd("Invalid camera normal vector", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_fov(line[3]))
	{
		ft_putendl_fd("Invalid camera field of view", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
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
