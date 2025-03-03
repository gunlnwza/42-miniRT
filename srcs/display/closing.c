/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:56:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/03 18:41:48 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

void	free_world(t_world *world)
{
	int	i;

	i = 0;
	while (i < world->nb_objects)
	{
		free(world->objects[i]);
		i++;
	}
}

void	free_data(t_data *data)
{
	free_world(&data->world);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
}
