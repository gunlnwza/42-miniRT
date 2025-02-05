/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 11:37:23 by nteechar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#define WIDTH 800
#define HEIGHT 600

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

// Print the window width and height.
static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	// printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
	(void) mlx;
}


int32_t	main(void)
{
	float	aspect_ratio = (float) WIDTH / HEIGHT;
	printf("float aspect_ratio = %f\n", aspect_ratio);

	float	focal_length = 1.0f;
	float	viewport_height = 2.0f;
	float	viewport_width = viewport_height * aspect_ratio;
	t_vector3 *camera_center = vector3_create(0, 0, 0);
	
	t_vector3 *viewport_h = vector3_create(viewport_width, 0 ,0);
	t_vector3 *viewport_v = vector3_create(0, -viewport_height ,0);

	t_vector3 *pixel_delta_h = vector3_copy(viewport_h);
	vector3_scalar_mul_ip(pixel_delta_h, 1.0f / WIDTH);
	
	t_vector3 *pixel_delta_v = vector3_copy(viewport_v);
	vector3_scalar_mul_ip(pixel_delta_h, 1.0f / HEIGHT);

	t_vector3 *viewport_upper_left = vector3_copy(camera_center);
	vector3_sub_ip(viewport_upper_left, vector3_create(0, 0, focal_length));
	vector3_sub_ip(viewport_upper_left, vector3_scalar_mul(viewport_h, 0.5));
	vector3_sub_ip(viewport_upper_left, vector3_scalar_mul(viewport_v, 0.5));

	t_vector3 *pixel00_loc = vector3_copy(viewport_upper_left);
	vector3_add_ip(pixel00_loc, viewport_upper_left);
	vector3_add_ip(pixel00_loc, vector3_scalar_mul(pixel_delta_h, 0.5));
	vector3_add_ip(pixel00_loc, vector3_scalar_mul(pixel_delta_v, 0.5));

	// Even after the image is being displayed, we can still modify the buffer.
	for (int y = 0; y < HEIGHT; y++)
	{
		ft_printf("Rendering: y=%i\r", y);
		for (int x = 0; x < WIDTH; x++)
		{
			t_vector3 *pixel_center = vector3_copy(pixel00_loc);
			vector3_add_ip(pixel_center, vector3_scalar_mul(pixel_delta_h, x));
			vector3_add_ip(pixel_center, vector3_scalar_mul(pixel_delta_v, y));

			/*
			auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
			*/
			
			// usleep(1);
		}
		ft_printf("                    \r");
	}
	ft_printf("Finish rendering\n");

	// MLX allows you to define its core behaviour before startup.

	// mlx_set_setting(MLX_MAXIMIZED, true);

	// mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	// if (!mlx)
	// 	ft_error();

	// Create and display the image.

	// mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
	// 	ft_error();

	// Register a hook and pass mlx as an optional param.

	// NOTE: Do this before calling mlx_loop!
	// mlx_loop_hook(mlx, ft_hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

// #include <stdlib.h>
// #include <string.h>

// // Bytes Per Pixel. Since each pixel is represented as an integer, it will be four bytes for four channels.
// #define BPP sizeof(int32_t)

// int32_t	main(void)
// {
//     // Init mlx with a canvas size of 256x256 and the ability to resize the window.
//     mlx_t* mlx = mlx_init(256, 256, "MLX42", true);
    
//     if (!mlx) exit(EXIT_FAILURE);

//     // Create a 128x128 image.
//     mlx_image_t* img = mlx_new_image(mlx, 128, 128);

//     // Set the channels of each pixel in our image to the maximum byte value of 255. 
//     memset(img->pixels, 255, img->width * img->height * BPP);

//     // Draw the image at coordinate (0, 0).
//     mlx_image_to_window(mlx, img, 0, 0);

//     // Run the main loop and terminate on quit.  
//     mlx_loop(mlx);
//     mlx_terminate(mlx);

//     return (EXIT_SUCCESS);
// }


// int main(int argc, char **argv)
// {
// 	if (argc == 1)
// 		return (1);

// 	(void) argv;
// 	return (0);
// }