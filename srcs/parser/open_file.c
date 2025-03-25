/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:16 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/03/25 11:19:34 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

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

// int	open_file(t_world *world, char *filename)
// {
// 	int     fd;
// 	int		number_of_lines;
// 	char    **lines;
// 	char	***tokens;

// 	if (!is_rt_file(filename))
// 	{
// 		show_error("Wrong file extension");
// 		return (ERROR);
// 	}
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		show_error("Failed to open file");
// 		return (ERROR);
// 	}
// 	lines = load_file(fd);
// 	if (lines == NULL)
// 	{
// 		return (ERROR);
// 	}
// 	number_of_lines = array_length(lines);
// 	tokens = split_lines(number_of_lines, lines);
// 	free_array(lines);
// 	if (tokens == NULL)
// 	{
// 		ft_putendl_fd("tokens", STDERR_FILENO);
// 		return (ERROR);
// 	}
// 	if (validate_scene(number_of_lines, tokens) != SUCCESS)
// 	{
// 		show_error("vaidate_scene");
// 		return (ERROR);
// 	}
// 	if (parse_scene(number_of_lines, tokens, world) != SUCCESS)
// 	{
// 		ft_putendl_fd("parse_scene", STDERR_FILENO);
// 		return (ERROR);
// 	}
// 	return (SUCCESS);
// }
