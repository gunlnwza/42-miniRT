/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <nteechar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:18 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/22 12:50:04 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int	get_rgba(int r, int g, int b, int a);

int	get_r(int rgba);
int	get_g(int rgba);
int	get_b(int rgba);
int	get_a(int rgba);

int	add_color(int color_a, int color_b);
int	multiply_color(int color_a, int color_b);

#endif
