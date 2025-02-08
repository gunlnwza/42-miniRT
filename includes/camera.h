#ifndef CAMERA_H
# define CAMERA_H

# include "utils.h"
# include "ray.h"
# include "world.h"
# include "constants.h"
# include "color.h"

typedef struct s_camera
{
	int			image_height;
	t_vector3	center;
	t_vector3	viewport_h;
	t_vector3	viewport_v;
	t_vector3	pixel00_loc;
	t_vector3	pixel_delta_h;
	t_vector3	pixel_delta_v;
}	t_camera;

void	init_camera(t_camera *camera);

int	is_ray_hit(const t_world *world, t_ray *ray, t_decimal ray_tmin, t_decimal ray_tmax, t_hit_record *rec);
int	ray_color(t_ray *ray, int depth, const t_world *world);

#endif
