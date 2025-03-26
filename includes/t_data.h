/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_data.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 01:31:29 by nteechar          #+#    #+#             */
/*   Updated: 2025/03/26 16:29:55 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_DATA_H
# define T_DATA_H

# include "world.h"

typedef enum e_mode
{
	MODE_DEFAULT,
	MODE_PARSE_ONLY,
	MODE_DEBUG
}	t_mode;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_world		world;
	t_mode		mode;
}	t_data;

#endif
