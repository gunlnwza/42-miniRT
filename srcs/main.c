/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 21:52:02 by nteechar         ###   ########.fr       */
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
		printf("Error\n");
		printf("Wrong arguments format\n");
		printf("Usage: ./miniRT *.rt [mode]\n");
		return (ERROR);
	}
	if (read_file_to_world(argv[1], &data->world) != SUCCESS)
		return (ERROR);
	if (data->mode == MODE_PARSE_ONLY)
	{
		printf("Parse OK\n");
		free_world(&data->world);
		exit(EXIT_SUCCESS);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (process_input(argc, argv, &data) != SUCCESS)
		return (EXIT_FAILURE);
	if (init_display(&data) != SUCCESS)
		return (EXIT_FAILURE);
	render_image(data.img, &data.world);
	mlx_loop(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
