# include "../../libs/MLX42/include/MLX42/MLX42.h"
# include "../../libs/libft/libft.h"

#include "../../includes/camera.h"

void	init_ray(t_ray *ray, t_camera *camera)
{
	v_copy(&ray->origin, &camera->center);
	v_copy(&ray->direction, &camera->pixel00_loc);
	v_sub(&ray->direction, &ray->origin);
}

void render_image(mlx_image_t *img, t_world *world, t_camera *camera)
{
	t_ray	ray;
	int		pixel_color;
	int		x;
	int		y;

	init_ray(&ray, camera);
	y = 0;
	while (y < HEIGHT)
	{
		ft_printf("\rRendering: y=%i", y);
		x = 0;
		while (x < WIDTH)
		{
			pixel_color = ray_color(&ray, world);
			mlx_put_pixel(img, x, y, pixel_color);
			x++;
			v_add(&ray.direction, &camera->pixel_delta_h);
		}
		y++;
		v_sub(&ray.direction, &camera->viewport_h);
		v_add(&ray.direction, &camera->pixel_delta_v);
	}
	ft_printf("\rFinish rendering!\n");
}
