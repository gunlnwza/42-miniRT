/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   openfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:16 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/03/22 11:53:54 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

static int	is_rt_file(char *filename)
{
	int	len;

	len = ft_strlen(filename) - 3;
	if (len > 3)
		return (ft_strncmp(filename + len, ".rt", 3) == 0);
	return (0);
}

char	*sanitize_line(char *line)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = line;
	while (tmp && tmp[++i])
	{
		if (tmp[i] == '\t' || tmp[i] == '\n')
			tmp[i] = ' ';
	}
	line = ft_strtrim(tmp, " ");
	free(tmp);
	return (line);
}

int	read_file(t_world *world, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line = sanitize_line(line);
		if (line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parse_params(world, line) != 0)
		{
			free(line);
			return (show_error("Failed to parse line"));
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	open_file(t_world *world, char *filename)
{
	int	fd;

	if (!is_rt_file(filename))
		return (show_error("Wrong file"));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (show_error("Failed to open file"));
	if (!read_file(world, fd))
		return (0);
	return (1);
}
