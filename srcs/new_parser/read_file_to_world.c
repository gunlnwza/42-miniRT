/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_to_world.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:48:00 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 16:26:47 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int	is_rt_file_extension(char *filename)
{
	char	*dot_ptr;
	char	*slash_ptr;
	int		name_len;

	dot_ptr = ft_strrchr(filename, '.');
	if (dot_ptr == NULL)
		return (FALSE);
	slash_ptr = ft_strrchr(filename, '/');
	if (slash_ptr)
		name_len = dot_ptr - (slash_ptr + 1);
	else
		name_len = dot_ptr - filename;
	if (name_len == 0)
		return (FALSE);
	return (ft_strcmp(dot_ptr, ".rt") == 0);
}

static int	open_file(char *filename)
{
	int	fd;

	if (!is_rt_file_extension(filename))
	{
		ft_putendl_fd("Error\nNot a .rt file", STDERR_FILENO);
		return (ERROR);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ERROR);
	return (fd);
}

static char	***split_lines(char **lines)
{
	int		number_of_lines;
	char	***tokens;
	int		i;

	number_of_lines = array_length(lines);
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
				free_array(tokens[--i]);
			free(tokens);
		}
		i++;
	}
	tokens[number_of_lines] = NULL;
	return (tokens);
}

int	read_file_to_world(char *filename, t_world *world)
{
	int		fd;
	char	**lines;
	int		number_of_lines;
	char	***file_tokens;

	fd = open_file(filename);
	if (fd < 0)
		return (ERROR);
	lines = load_file_into_memory(fd);
	if (lines == NULL)
		return (ERROR);
	number_of_lines = array_length(lines);
	file_tokens = split_lines(lines);
	free_array(lines);
	if (file_tokens == NULL)
		return (ERROR);
	if (validate_scene(number_of_lines, file_tokens) != SUCCESS)
		return (ERROR);
	if (parse_scene(number_of_lines, file_tokens, world) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
