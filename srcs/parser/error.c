/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykai-yua <ykai-yua@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:46:09 by ykai-yua          #+#    #+#             */
/*   Updated: 2025/02/25 17:46:09 by ykai-yua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

int	show_parsing_error(t_world *world, char **params, const char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	if (world->nb_objects > 0)
	{
		ft_putstr_fd(" [object index:", 2);
		ft_putnbr_fd(world->nb_objects, 2);
		ft_putstr_fd("]", 2);
	}
	ft_putendl_fd("", 2);
	free_array(params);
	return (1);
}

int	show_error(const char *msg)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putendl_fd("", 2);
	return (1);
}
