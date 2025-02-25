/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:25 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/02/25 17:46:25 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

int	parse_camera(t_world *world, char **params)
{
	if (array_length(params) != 4)
	{
		free_array(params);
		return (show_error("Invalid camera parameters"));
	}
	\
	parse_vector(params[1], &world->camera.center);
	parse_vector(params[2], &world->camera.normal);
	world->camera.deg_fov = ft_atoi(params[3]);
	\
	free_array(params);
	return (0);
}

int	parse_ambient(t_world *world, char **params)
{
	double	brightness;
	int		r;
	int		g;
	int		b;

	if (array_length(params) != 3)
	{
		free_array(params);
		return (show_error("Invalid ambient parameters"));
	}
	brightness = ft_atof(params[1]);
	if (ft_sscanf(params[2], &r, &g, &b) != 3)
	{
		free_array(params);
		return (show_error("Invalid ambient color format"));
	}
	world->ambient_light_color = get_rgba((r * brightness),
			(g * brightness), (b * brightness), 255);
	free_array(params);
	return (0);
}

int	parse_light(t_world *world, char **params)
{
	double	brightness;
	int		r;
	int		g;
	int		b;

	if (array_length(params) != 4)
	{
		free_array(params);
		return (show_error("Invalid light parameters"));
	}
	\
	parse_vector(params[1], &world->light.point);
	brightness = ft_atof(params[2]);
	if (ft_sscanf(params[3], &r, &g, &b) != 3)
	{
		free_array(params);
		return (show_error("Invalid light color format"));
	}
	world->light.color = get_rgba((int)(r * brightness),
			(int)(g * brightness), (int)(b * brightness), 255);
	free_array(params);
	return (0);
}
