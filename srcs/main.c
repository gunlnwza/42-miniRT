/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 16:32:07 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

void	render_image(mlx_image_t *img, t_world *world, t_camera *camera);
int		init_world_and_camera(t_world *world, t_camera *camera);  // replace with parser

void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	(void) mlx;
}

void ft_close(void *param)
{
	exit(0);
	(void) param;
}

void	ft_keypress(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE)
		exit(0);
	(void) param;
}

int	init_display(mlx_t **mlx, mlx_image_t **img)
{
	*mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (*mlx == NULL)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (ERROR);
	}
	*img = mlx_new_image(*mlx, WIDTH, HEIGHT);
	if (*img == NULL || (mlx_image_to_window(*mlx, *img, 0, 0) < 0))
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putendl_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		return (ERROR);
	}
	mlx_close_hook(*mlx, ft_close, NULL);
	mlx_key_hook(*mlx, ft_keypress, NULL);
	mlx_loop_hook(*mlx, ft_hook, *mlx);
	return (SUCCESS);
}

int	main(void)
{
	t_world		world;
	t_camera	camera;
	mlx_t		*mlx;
	mlx_image_t	*img;

	if (init_world_and_camera(&world, &camera) == ERROR)  // replace with parser
		return (EXIT_FAILURE);
	mlx = NULL;
	img = NULL;
	if (init_display(&mlx, &img) == ERROR)
		return (EXIT_FAILURE);
	render_image(img, &world, &camera);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
