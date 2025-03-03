/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:56:57 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/03 16:57:41 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

void    free_world(t_world *world)
{
	(void) world;
}

void    free_data(t_data *data)
{
    free_world(&data->world);
    mlx_delete_image(data->mlx, data->img);
    mlx_terminate(data->mlx);
}

void	ft_close(void *data_)
{
	t_data	*data;

	data = data_;
	(void) data;
	exit(0);
}
