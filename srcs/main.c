/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/22 11:53:48 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
    if (argc != 2)
    {
        ft_putendl_fd("Error: Wrong number of arguments", STDERR_FILENO);
        ft_putendl_fd("Usage: ./miniRT *.rt", STDERR_FILENO);
        return (EXIT_FAILURE);
    }
	if (open_file(&data.world, argv[1]) != SUCCESS)
	{
		ft_putendl_fd("Error: Invalid scene file", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
    ft_putendl_fd("\033[32mParsing OK\033[0m", STDOUT_FILENO);
	if (init_display(&data) != SUCCESS)
		return (EXIT_FAILURE);
	render_image(data.img, &data.world);
	mlx_loop(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
