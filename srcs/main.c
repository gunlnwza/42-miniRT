/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 11:23:32 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

#define MODE_DEFAULT 0
#define MODE_PARSE_ONLY 1
#define MODE_MODIFY_CAMERA 2

static int	parse_option(int argc, char **argv, t_data *data)
{
	if (argc == 2)
		return (SUCCESS);
	if (argc != 3)
		return (ERROR);
	\
	if (ft_strcmp(argv[2], "--default") == 0)
		data->mode = MODE_DEFAULT;
	else if (ft_strcmp(argv[2], "--parse-only") == 0)
		data->mode = MODE_PARSE_ONLY;
	else if (ft_strcmp(argv[2], "--modify-camera") == 0)
		data->mode = MODE_MODIFY_CAMERA;
	else
		return (ERROR);
	\
	return (SUCCESS);
}

static int	process_input(int argc, char **argv, t_data *data)
{
	if (parse_option(argc, argv, data) != SUCCESS)
	{
		ft_putendl_fd("Error\nWrong arguments format", STDERR_FILENO);
		ft_putendl_fd("Usage: ./miniRT *.rt [mode]", STDERR_FILENO);
		return (ERROR);
	}
	if (read_file_to_world(argv[1], &data->world) != SUCCESS)
	{
		ft_putendl_fd("Error: error opening file", STDERR_FILENO);
		return (ERROR);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (process_input(argc, argv, &data) != SUCCESS)
		return (EXIT_FAILURE);
	if (data.mode == MODE_PARSE_ONLY)
	{
		ft_putendl_fd("Parsing OK", STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	if (init_display(&data) != SUCCESS)
		return (EXIT_FAILURE);
	render_image(data.img, &data.world);
	mlx_loop(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
