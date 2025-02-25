/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/25 15:54:12 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

// int	main(int argc, char **argv)
// {
// 	t_data	data;

// 	ft_bzero(&data, sizeof(t_data));
// 	if (argc != 2 || open_file(&data.world, argv[1]) != 0)
// 	{
// 		ft_putstr_fd("Error: Invalid scene file\n", STDERR_FILENO);
// 		return (EXIT_FAILURE);
// 	}
// 	if (init_display(&data) == ERROR)
// 		return (EXIT_FAILURE);
// 	configure_camera(&data.world.camera);
// 	render_image(data.img, &data.world);
// 	mlx_loop(data.mlx);
// 	mlx_terminate(data.mlx);
// 	return (EXIT_SUCCESS);
// }

int	main(int argc, char **argv)
{
	int	i = 1;

	while (i < argc)
	{
		double a = atof(argv[i]); 
		double b = ft_atof(argv[i]);

		if (a == b)
			printf("%i. OK (a = %f, b = %f)\n", i, a, b);
		else
			printf("%i. \033[31mKO\033[0m (a = %f, b = %f)\n", i, a, b);

		i++;
	}
	// printf("\n");

	return (EXIT_SUCCESS);
}
