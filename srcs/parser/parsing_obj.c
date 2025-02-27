/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:54:55 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/22 12:54:55 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

int	parse_plane(t_world *world, char **params)
{
	int			i;
	t_object	obj;

	i = 0;
	ft_bzero(&obj, sizeof(t_object));
	obj.type = PLANE;
	while (params && params[++i])
	{
		if (i == 1 && parse_vector(params[i], &obj.point))
			return (show_parsing_error(world, params, "Invalid number of coordinates"));
		if (i == 2 && parse_vector(params[i], &obj.normal))
			return (show_parsing_error(world, params, "Invalid number of orientations"));
		if (i == 3 && parse_color(params[i], &obj.color))
			return (show_parsing_error(world, params, "Invalid number of colors"));
	}
	v_normalize_ip(&obj.normal);
	add_plane(world, &obj.point, &obj.normal, obj.color);
	return (0);
}

int	parse_sphere(t_world *world, char **params)
{
	int			i;
	t_object	obj;

	i = 0;
	ft_bzero(&obj, sizeof(t_object));
	obj.type = SPHERE;
	while (params && params[++i])
	{
		if (i == 1 && parse_vector(params[i], &obj.point))
			return (show_parsing_error(world, params, "Invalid number of coordinates"));
		if (i == 2 && parse_double(params[i], &obj.radius))  // TODO: actually need to be diameter?
			return (show_parsing_error(world, params, "Not a double"));
		if (i == 3 && parse_color(params[i], &obj.color))
			return (show_parsing_error(world, params, "Invalid number of colors"));
	}
	add_sphere(world, &obj.point, obj.radius, obj.color);
	return (0);
}

int	parse_cylinder(t_world *world, char **params)
{
	int			i;
	t_object	obj;

	i = 0;
	ft_bzero(&obj, sizeof(t_object));
	obj.type = CYLINDER;
	while (params && params[++i])
	{
		if (i == 1 && parse_vector(params[i], &obj.point))
			return (show_parsing_error(world, params, "Invalid number of coordinates"));
		if (i == 2 && parse_vector(params[i], &obj.normal))
			return (show_parsing_error(world, params, "Invalid number of orientations"));
		if (i == 3 && parse_double(params[i], &obj.radius))
			return (show_parsing_error(world, params, "Not a double"));
		if (i == 4 && parse_double(params[i], &obj.height))
			return (show_parsing_error(world, params, "Not a double"));
		if (i == 5 && parse_color(params[i], &obj.color))
			return (show_parsing_error(world, params, "Invalid number of colors"));
	}
	v_normalize_ip(&obj.normal);
	add_cylinder(world, &obj.point, &obj.normal, obj.color, obj.radius, obj.height);
	return (0);
}
