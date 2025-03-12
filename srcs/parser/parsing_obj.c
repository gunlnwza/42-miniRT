/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:33 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/02/25 17:46:33 by ykai-yua         ###   ########.fr       */
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
	if (array_length(params) !=  4)
	{
		free_array(params);
		return (show_error("Invalid plane parameters"));
	}
	while (params && params[++i])
	{
		if (i == 1 && parse_vector(params[i], &obj.point))
			return (show_parsing_error(world, params,
					"Invalid number of coordinates"));
		if (i == 2 && parse_vector(params[i], &obj.normal))
			return (show_parsing_error(world, params,
					"Invalid number of orientations"));
		if (i == 3 && parse_color(params[i], &obj.color))
			return (show_parsing_error(world, params,
					"Invalid number of colors"));
	}
	v_normalize_ip(&obj.normal);
	add_plane(world, &obj.point, &obj.normal, obj.color);
	return (0);
}

int	parse_sphere(t_world *world, char **params)
{
	int			i;
	t_object	obj;
	double		diameter;

	i = 0;
	ft_bzero(&obj, sizeof(t_object));
	obj.type = SPHERE;
	if (array_length(params) !=  4)
	{
		free_array(params);
		return (show_error("Invalid sphere parameters"));
	}
	while (params && params[++i])
	{
		if (i == 1 && parse_vector(params[i], &obj.point))
			return (show_parsing_error(world, params, "Invalid number of coordinates"));
		if (i == 2 && parse_double(params[i], &diameter))
			return (show_parsing_error(world, params, "Not a double"));
		if (i == 3 && parse_color(params[i], &obj.color))
			return (show_parsing_error(world, params,
					"Invalid number of colors"));
	}
	obj.radius = diameter / 2;
	add_sphere(world, &obj.point, obj.radius, obj.color);
	return (0);
}

int	parse_cylinder(t_world *world, char **params)
{
	int			i;
	t_object	obj;
	double		diameter;

	i = 0;
	ft_bzero(&obj, sizeof(t_object));
	obj.type = CYLINDER;
	if (array_length(params) !=  6)
	{
		free_array(params);
		return (show_error("Invalid cylinder parameters"));
	}
	while (params && params[++i])
	{
		if (i == 1 && parse_vector(params[i], &obj.point))
			return (show_parsing_error(world, params,
					"Invalid number of coordinates"));
		if (i == 2 && parse_vector(params[i], &obj.normal))
			return (show_parsing_error(world, params,
					"Invalid number of orientations"));
		if (i == 3 && parse_double(params[i], &diameter))
			return (show_parsing_error(world, params, "Not a double"));
		if (i == 4 && parse_double(params[i], &obj.height))
			return (show_parsing_error(world, params, "Not a double"));
		if (i == 5 && parse_color(params[i], &obj.color))
			return (show_parsing_error(world, params, "Invalid num"));
	}
	obj.radius = diameter / 2;
	v_normalize_ip(&obj.normal);
	add_cylinder(world, &obj.point, &obj.normal,
		obj.color, obj.radius, obj.height);
	return (0);
}
