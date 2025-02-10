#ifndef CAMERA_H
# define CAMERA_H

# include <math.h>

# include "utils.h"
# include "ray.h"
# include "world.h"
# include "constants.h"
# include "color.h"

typedef struct s_camera
{
	t_vector3	center;
	t_vector3	viewport_h;
	t_vector3	viewport_v;
	t_vector3	pixel_delta_h;
	t_vector3	pixel_delta_v;
	t_vector3	pixel00_loc;
}	t_camera;

void	configure_camera(t_camera *camera, const t_vector3 *point, const t_vector3 *normal, int deg_fov);

int	is_ray_hit(const t_world *world, t_ray *ray, t_hit_record *rec);
int	ray_color(t_ray *ray, const t_world *world);

#endif
