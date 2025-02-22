/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:54:45 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/22 12:54:45 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

int	parse_params(t_world *world, char *line)
{
	char	**params;

	params = ft_split(line, ' ');
	if (!params || !params[0])
	{
		free_array(params);
		return (0);
	}
	if (ft_strncmp(params[0], "A", 1) == 0)
	{
		if (parse_ambient(world, params) != 0)
			return (show_error("Failed to parse ambient light"));
	}
	else if (ft_strncmp(params[0], "C", 1) == 0)
	{
		if (parse_camera(world, params) != 0)
			return (show_error("Failed to parse camera"));
	}
	else if (ft_strncmp(params[0], "L", 1) == 0)
	{
		if (parse_light(world, params) != 0)
			return (show_error("Failed to parse light"));
	}
	else if (ft_strncmp(params[0], "sp", 2) == 0)
	{
		if (parse_sphere(world, params) != 0)
			return (show_error("Failed to parse sphere"));
	}
	else if (ft_strncmp(params[0], "pl", 2) == 0)
	{
		if (parse_plane(world, params) != 0)
			return (show_error("Failed to parse plane"));
	}
	else if (ft_strncmp(params[0], "cy", 2) == 0)
	{
		if (parse_cylinder(world, params) != 0)
			return (show_error("Failed to parse cylinder"));
	}
	else
	{
		free_array(params);
		return (show_error("Unknown object type"));
	}
	return (0);
}
