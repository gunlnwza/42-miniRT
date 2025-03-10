/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/03 18:47:03 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (argc != 2 || open_file(&data.world, argv[1]) != 0)
	{
		ft_putstr_fd("Error: Invalid scene file\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (init_display(&data) == ERROR)
		return (EXIT_FAILURE);
	render_image(data.img, &data.world);
	mlx_loop(data.mlx);
	free_data(&data);
	return (EXIT_SUCCESS);
}
