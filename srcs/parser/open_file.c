/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:16 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/03/25 08:16:41 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

typedef enum e_scene_type
{
	SCENE_AMBIENT,
	SCENE_CAMERA,
	SCENE_LIGHT,
	SCENE_SPHERE,
	SCENE_PLANE,
	SCENE_CYLINDER,
	SCENE_INVALID
}	t_scene_type;

static int	is_rt_file(char *filename)
{
	char	*dot_ptr;
	char	*slash_ptr;
	int		name_len;

	dot_ptr = ft_strrchr(filename, '.');
	if (dot_ptr == NULL)
		return (FALSE);
	slash_ptr = ft_strrchr(filename, '/');
	if (slash_ptr == NULL)
		name_len = dot_ptr - filename;
	else
		name_len = dot_ptr - (slash_ptr + 1);
	if (name_len == 0)
		return (FALSE);
	return (ft_strcmp(dot_ptr, ".rt") == 0);
}

char	*sanitize_line(char *line)
{
	int		i;
	char	*old_line;

	i = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			line[i] = ' ';
		i++;
	}
	old_line = line;
	line = ft_strtrim(line, " ");
	free(old_line);
	if (line == NULL)
		return (NULL);
	return (line);
}

// int	read_file(t_world *world, int fd)
// {
// 	char	*line;
// 
// 	while (TRUE)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			return (SUCCESS);
// 		line = sanitize_line(line);
// 		if (line == NULL)
// 			return (ERROR);
// 		if (line[0] == '#' || line[0] == '\0')
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		if (parse_params(world, line) != 0)
// 		{
// 			free(line);
// 			show_error("Failed to parse line");
// 			return (ERROR);
// 		}
// 		free(line);
// 	}
// }

char **load_file(int fd)
{
	t_list  *node;
	char    *line;
	char    **lines;

	node = NULL;
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		line = sanitize_line(line);
		if (line == NULL)
		{
			ft_lstclear(&node, free);
			return (NULL);
		}
		if (line[0] == '#' || ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if (ft_lstnew_add_back(&node, line) == NULL)
		{
			free(line);
			ft_lstclear(&node, free);
			return (NULL);
		}
	}

	// another function, transform linked list into array
	size_t	i;
	size_t	len;
	t_list	*ptr;

	len = ft_lstsize(node);
	lines = malloc((len + 1) * sizeof(char *));
	if (lines == NULL)
		return (NULL);
	i = 0;
	ptr = node;
	while (i < len)
	{
		lines[i] = ptr->content;
		i++;
		ptr = ptr->next;
	}
	lines[len] = NULL;
	ft_lstclear(&node, NULL);
	return (lines);
}

char	***split_lines(int number_of_lines, char **lines)
{
	char	***tokens;
	int		i;

	tokens = malloc((number_of_lines + 1) * sizeof(char **));
	if (tokens == NULL)
		return (NULL);
	i = 0;
	while (i < number_of_lines)
	{
		tokens[i] = ft_split(lines[i], ' ');
		if (tokens[i] == NULL)
		{
			while (i > 0)
			{
				i--;
				free_array(tokens[i]);
			}
			free(tokens);
		}
		i++;
	}
	tokens[number_of_lines] = NULL;
	return (tokens);
}

t_scene_type	identify_type(char *id)
{
	if (ft_strcmp(id, "A") == 0)
		return (SCENE_AMBIENT);
	if (ft_strcmp(id, "C") == 0)
		return (SCENE_CAMERA);
	if (ft_strcmp(id, "L") == 0)
		return (SCENE_LIGHT);
	if (ft_strcmp(id, "sp") == 0)
		return (SCENE_SPHERE);
	if (ft_strcmp(id, "pl") == 0)
		return (SCENE_PLANE);
	if (ft_strcmp(id, "cy") == 0)
		return (SCENE_CYLINDER);
	return (SCENE_INVALID);
}

int	is_in_range(int min, int max, int x)
{
	return (min <= x && x <= max);
}

int	is_in_rangef(double min, double max, double x)
{
	return (min <= x && x <= max);
}

int	is_same_after_ft_atoi(const char *nptr)
{
	int		value;
	char	*after;
	int		ret;

	value = ft_atoi(nptr);
	after = ft_itoa(value);
	if (after == NULL)
		return (FALSE);
	ret = ft_strcmp(nptr, after);
	free(after);
	return (ret == 0);
}

int	is_valid_ratio(char *ratio)
{
	double	value;
	char	*endptr;

	value = ft_strtod(ratio, &endptr);
	if (*endptr != '\0')
		return (FALSE);
	if (!is_in_rangef(0, 1, value))
		return (FALSE);
	return (TRUE);
}

int	is_valid_color(char *rgb_str)
{
	char	**rgb;
	int		value;
	char	*endptr;
	int		i;

	rgb = ft_split(rgb_str, ',');
	if (rgb == NULL)
		return (FALSE);
	if (array_length(rgb) != 3)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		value = ft_strtol(rgb[i], &endptr);
		if (*endptr != '\0' || !is_in_range(0, 255, value))
			return (FALSE);
		i++;
	}	
	free_array(rgb);
	return (TRUE);
}

int	is_valid_pos(char *pos_str)
{
	double	value;
	char	*endptr;
	char	**xyz;
	int		i;

	xyz = ft_split(pos_str, ',');
	if (xyz == NULL)
		return (FALSE);
	if (array_length(xyz) != 3)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		value = ft_strtod(xyz[i], &endptr);
		if (*endptr != '\0')
			return (FALSE);
		i++;
	}
	(void) value;
	return (TRUE);
}

int	is_valid_normal(char *normal_str)
{
	double	value;
	char	*endptr;
	char	**xyz;
	int		i;

	xyz = ft_split(normal_str, ',');
	if (xyz == NULL)
		return (FALSE);
	i = 0;
	while (i < 3)
	{
		value = ft_strtod(xyz[i], &endptr);
		if (*endptr != '\0' || !is_in_rangef(-1, 1, value))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_valid_length(char *length_str)
{
	double	value;
	char	*endptr;

	value = ft_strtod(length_str, &endptr);
	if (*endptr != '\0' || value <= 0)
		return (FALSE);
	return (TRUE);
}

int	is_valid_fov(char *fov_str)
{
	int		value;
	char	*endptr;

	value = ft_strtol(fov_str, &endptr);
	if (*endptr != '\0' || !is_in_rangef(0, 180, value))
		return (FALSE);
	return (TRUE);
}

int	validate_ambient(char **line)
{
	if (array_length(line) != 3)
	{
		ft_putendl_fd("Invalid ambient parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_ratio(line[1]))
	{
		ft_putendl_fd("Invalid ambient brightness", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[2]))
	{
		ft_putendl_fd("Invalid ambient color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

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

int	validate_light(char **line)
{
	if (array_length(line) != 4)
	{
		ft_putendl_fd("Invalid light parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_pos(line[1]))
	{
		ft_putendl_fd("Invalid light position", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_ratio(line[2]))
	{
		ft_putendl_fd("Invalid light brightness", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[3]))
	{
		ft_putendl_fd("Invalid light color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	validate_sphere(char **line)
{
	if (array_length(line) != 4)
	{
		ft_putendl_fd("Invalid sphere parameters", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_pos(line[1]))
	{
		ft_putendl_fd("Invalid sphere position", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_length(line[2]))
	{
		ft_putendl_fd("Invalid sphere diameter", STDERR_FILENO);
		return (ERROR);
	}
	if (!is_valid_color(line[3]))
	{
		ft_putendl_fd("Invalid sphere color", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

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

int	validate_scene(int number_of_lines, char ***tokens)
{
	int				i;
	char			**line;
	t_scene_type	type;

	i = 0;
	while (i < number_of_lines)
	{
		line = tokens[i];
		type = identify_type(line[0]);
		if ((type == SCENE_AMBIENT && validate_ambient(line) != SUCCESS)
			|| (type == SCENE_CAMERA && validate_camera(line) != SUCCESS)
			|| (type == SCENE_LIGHT && validate_light(line) != SUCCESS)
			|| (type == SCENE_SPHERE && validate_sphere(line) != SUCCESS)
			|| (type == SCENE_PLANE && validate_plane(line) != SUCCESS)
			|| (type == SCENE_CYLINDER && validate_cylinder(line) != SUCCESS)
			|| (type == SCENE_INVALID))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}


double	parse_ratio(char *ratio_str)
{
	double	ratio;

	ratio = ft_strtod(ratio_str, NULL);
	return (ratio);
}

int parse_color(char *rgb_str, int *color)
{
	char	**rgb;

	rgb = ft_split(rgb_str, ',');
	if (rgb == NULL)
		return (ERROR);
	*color = get_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	free_array(rgb);
	return (SUCCESS);
}

int	parse_vector(char *xyz_str, t_vector3 *dest)
{
	char	**xyz;

	xyz = ft_split(xyz_str, ',');
	if (xyz == NULL)
		return (ERROR);
	dest->x = ft_atof(xyz[0]);
	dest->y = ft_atof(xyz[1]);
	dest->z = ft_atof(xyz[2]);
	free_array(xyz);
	return (SUCCESS);
}

int	parse_normal_vector(char *normal_str, t_vector3 *dest)
{
	if (parse_vector(normal_str, dest) != SUCCESS)
		return (ERROR);
	v_normalize_ip(dest);
	return (SUCCESS);
}

int	parse_fov(char *fov_str)
{
	return (ft_atoi(fov_str));
}

int	parse_ambient(char **line, t_world *world)
{
	int		color;
	double	ratio;

	ratio = parse_ratio(line[1]);
	if (parse_color(line[2], &color) < 0)
		return (ERROR);
	world->ambient_light_color = scale_color(color, ratio);
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

int	parse_light(char **line, t_world *world)
{
	int		ret;
	int		color;
	double	ratio;

	ret = parse_vector(line[1], &world->light.point);
	if (ret != SUCCESS)
		return (ERROR);
	ratio = parse_ratio(line[2]);
	if (parse_color(line[3], &color) != SUCCESS)
		return (ERROR);
	world->light.color = scale_color(color, ratio);
	return (SUCCESS);
}

int	parse_sphere(char **line, t_world *world)
{
	t_object	*object;

	object = malloc(sizeof(t_object));
	if (object == NULL)
		return (ERROR);
	object->type = SPHERE;
	if (parse_vector(line[1], &object->point) < 0)
	{
		free(object);
		return (ERROR);
	}
	object->radius = ft_atof(line[2]) / 2;
	if (parse_color(line[3], &object->color) != SUCCESS)
	{
		free(object);
		return (ERROR);
	}
	world->objects[world->nb_objects++] = object;
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

int	parse_scene(int number_of_lines, char ***tokens, t_world *world)
{
	int				i;
	char			**line;
	t_scene_type	type;

	i = 0;
	while (i < number_of_lines)
	{
		line = tokens[i];
		type = identify_type(line[0]);
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

int	open_file(t_world *world, char *filename)
{
	int     fd;
	int		number_of_lines;
	char    **lines;
	char	***tokens;

	if (!is_rt_file(filename))
	{
		show_error("Wrong file extension");
		return (ERROR);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		show_error("Failed to open file");
		return (ERROR);
	}
	lines = load_file(fd);
	if (lines == NULL)
	{
		return (ERROR);
	}
	number_of_lines = array_length(lines);
	tokens = split_lines(number_of_lines, lines);
	free_array(lines);
	if (tokens == NULL)
	{
		ft_putendl_fd("tokens", STDERR_FILENO);
		return (ERROR);
	}
	if (validate_scene(number_of_lines, tokens) != SUCCESS)
	{
		show_error("vaidate_scene");
		return (ERROR);
	}
	if (parse_scene(number_of_lines, tokens, world) != SUCCESS)
	{
		ft_putendl_fd("parse_scene", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}
