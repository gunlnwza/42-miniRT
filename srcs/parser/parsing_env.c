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
	if (parse_vector(params[1], &world->camera.center))
	{
		free_array(params);
		return (show_error("Invalid camera center vector"));
	}
	if (parse_vector(params[2], &world->camera.normal))
	{
		free_array(params);
		return (show_error("Invalid camera normal vector"));
	}
	if (world->camera.normal.x < -1.0 || world->camera.normal.x > 1.0 ||
		world->camera.normal.y < -1.0 || world->camera.normal.y > 1.0 ||
		world->camera.normal.z < -1.0 || world->camera.normal.z > 1.0)
	{
		free_array(params);
		return (show_error("Invalid camera normal vector"));
	}
	if (!is_valid_number(params[3]))
	{
		free_array(params);
		return (show_error("Invalid field of view"));
	}
	world->camera.deg_fov = ft_atoi(params[3]);
	if (world->camera.deg_fov < 0 || world->camera.deg_fov > 180)
	{
		free_array(params);
		return (show_error("Invalid field of view"));
	}
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
	if (!is_valid_double(params[1]))
	{
		free_array(params);
		return (show_error("Invalid ambient brightness"));
	}
	brightness = ft_atof(params[1]);
	if (brightness < 0.0 || brightness > 1.0)
	{
		free_array(params);
		return (show_error("Invalid ambient brightness"));
	}
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
	if (parse_vector(params[1], &world->light.point))
	{
		free_array(params);
		return (show_error("Invalid light point"));
	}
	if (!is_valid_double(params[2]))
	{
		free_array(params);
		return (show_error("Invalid light brightness"));
	}
	brightness = ft_atof(params[2]);
	if (brightness < 0.0 || brightness > 1.0)
	{
		free_array(params);
		return (show_error("Invalid light brightness"));
	}
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

int	is_valid_double(const char *str)
{
	int has_digits;
	int has_decimal;

	has_digits = 0;
	has_decimal = 0;
	if (*str == '\0')
		return 0;
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
	{
		has_digits = 1;
		str++;
	}
	if (*str == '.')
	{
		has_decimal = 1;
		str++;
		while (*str)
		{
			if (!ft_isdigit(*str))
				has_digits = 0;
			str++;
		}
	}
	return (has_digits && (has_decimal || *str == '\0'));
}
