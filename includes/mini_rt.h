/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:53:15 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/25 21:39:41 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "parser.h"
# include "world_and_camera.h"

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_world		world;
	int			mode;
}	t_data;

int		init_display(t_data *data);
void	render_image(mlx_image_t *img, t_world *world);

int		is_modify_camera_key(keys_t key);
void	modify_camera(t_camera *camera, keys_t key);

void	free_world(t_world *world);
void	free_data(t_data *data);

#endif
