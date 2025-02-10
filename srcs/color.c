/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:07 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/10 12:12:04 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RRRRRRRR GGGGGGGG BBBBBBBB AAAAAAAA

// 'Encodes' four individual bytes into an int.
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

// Get the red channel.
int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

// Get the green channel.
int get_g(int rgba)
{
    // Move 2 bytes to the right and mask out the first byte.
    return ((rgba >> 16) & 0xFF);
}

// Get the blue channel.
int get_b(int rgba)
{
    // Move 1 byte to the right and mask out the first byte.
    return ((rgba >> 8) & 0xFF);
}

// Get the alpha channel.
int get_a(int rgba)
{
    // Move 0 bytes to the right and mask out the first byte.
    return (rgba & 0xFF);
}

int add_color(int color_a, int color_b)
{
    int r;
    int g;
    int b;

    r = get_r(color_a) + get_r(color_b);
    if (r > 255)
        r = 255;
    g = get_g(color_a) + get_g(color_b);
    if (g > 255)
        g = 255;
    b = get_b(color_a) + get_b(color_b);
    if (b > 255)
        b = 255;
    return (get_rgba(r, g, b, 255));
}

int multiply_color(int color_a, int color_b)
{
    int r;
    int g;
    int b;

    r = (get_r(color_a) * get_r(color_b)) / 255;
    if (r > 255)
        r = 255;
    g = (get_g(color_a) * get_g(color_b)) / 255;
    if (g > 255)
        g = 255;
    b = (get_b(color_a) * get_b(color_b)) / 255;
    if (b > 255)
        b = 255;
    return (get_rgba(r, g, b, 255));
}
