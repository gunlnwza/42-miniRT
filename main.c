/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nteechar <techazuza@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:49:26 by nteechar          #+#    #+#             */
/*   Updated: 2025/02/05 12:21:31 by nteechar         ###   ########.fr       */
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

int	ray_color(t_vector3 *ray_point, t_vector3 *ray_dir)
{
	t_vector3	unit_dir;

	vector3_copy_ip(&unit_dir, ray_dir);
	vector3_normalize_ip(&unit_dir);

	float a = 0.5 * (unit_dir.y + 1.0);

	int r;
	int g;
	int b;

	r = (1.0 - a) * 255 + a * 0.5 * 255;
	g = (1.0 - a) * 255 + a * 0.7 * 255;
	b = (1.0 - a) * 255 + a * 1.0 * 255;

	(void) ray_point;
	(void) ray_dir;
	return (get_rgba(r, g, b, 255));
}


int32_t	main(void)
{
	float	aspect_ratio = (float) WIDTH / HEIGHT;
	printf("float aspect_ratio = %f\n", aspect_ratio);

	float		focal_length = 1.0f;
	float		viewport_height = 2.0f;
	float		viewport_width = viewport_height * aspect_ratio;
	t_vector3	*camera_center = vector3_create(0, 0, 0);  // the scene camera
	
	t_vector3	*viewport_h = vector3_create(viewport_width, 0 ,0);
	t_vector3	*viewport_v = vector3_create(0, -viewport_height ,0);

	t_vector3	*pixel_delta_h = vector3_copy(viewport_h);
	vector3_scalar_mul_ip(pixel_delta_h, 1.0f / WIDTH);
	
	t_vector3	*pixel_delta_v = vector3_copy(viewport_v);
	vector3_scalar_mul_ip(pixel_delta_v, 1.0f / HEIGHT);

	t_vector3	*temp_vector = vector3_create(0, 0, 0);

	t_vector3	*viewport_upper_left = vector3_copy(camera_center);
	
	vector3_set_values_ip(temp_vector, 0, 0, focal_length);
	vector3_sub_ip(viewport_upper_left, temp_vector);

	vector3_copy_ip(temp_vector, viewport_h);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_sub_ip(viewport_upper_left, temp_vector);
	
	vector3_copy_ip(temp_vector, viewport_v);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_sub_ip(viewport_upper_left, temp_vector);

	t_vector3	*pixel00_loc = vector3_copy(viewport_upper_left);

	vector3_copy_ip(temp_vector, pixel_delta_h);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_add_ip(pixel00_loc, temp_vector);
	
	vector3_copy_ip(temp_vector, pixel_delta_v);
	vector3_scalar_mul_ip(temp_vector, 0.5);
	vector3_add_ip(pixel00_loc, temp_vector);

	t_vector3	*pixel_center = vector3_copy(pixel00_loc);
	t_vector3	*ray_direction = vector3_create(0, 0, 0);
	int			pixel_color;
	int			x;
	int			y;

	// mlx_set_setting(MLX_MAXIMIZED, true); // set the window to max size on start
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);  // create and display image
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	for (y = 0; y < HEIGHT; y++)
	{
		ft_printf("Rendering: y=%i", y);
		for (x = 0; x < WIDTH; x++)
		{
			vector3_copy_ip(ray_direction, pixel_center);
			vector3_sub_ip(ray_direction, camera_center);
			
			// ray is (point=camera_center, dir=ray_direction);  (ray_direction = pixel_center - camera_center)
            pixel_color = ray_color(camera_center, ray_direction);
			mlx_put_pixel(img, x, y, pixel_color);
			
			vector3_add_ip(pixel_center, pixel_delta_h);
		}
		ft_printf("                    \r");
		vector3_sub_ip(pixel_center, viewport_h);
		vector3_add_ip(pixel_center, pixel_delta_v);
	}
	ft_printf("Finish rendering\n");

	// Register a hook and pass mlx as an optional param. NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
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