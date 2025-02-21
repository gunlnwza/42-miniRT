#ifndef WORLD_AND_CAMERA_H
# define WORLD_AND_CAMERA_H

# include "libs.h"
# include "object.h"
# include "color.h"

typedef struct s_camera
{
	t_vector3	center;
	int			deg_fov;
	t_vector3	normal;
	t_vector3	viewport_h;
	t_vector3	viewport_v;
	t_vector3	pixel_delta_h;
	t_vector3	pixel_delta_v;
	t_vector3	pixel00_loc;
}	t_camera;

typedef struct s_light
{
	int			color;
	t_vector3	point;
}	t_light;

typedef struct s_world
{
	t_object	*objects[10];
	int			nb_objects;

	t_light		light;
	int			ambient_light_color;
}	t_world;


void	configure_camera(t_camera *camera, const t_vector3 *point, const t_vector3 *normal, int deg_fov);

int		is_ray_hit(t_world *world, t_ray *ray, t_hit_record *rec);
int		ray_color(t_ray *ray, t_world *world);


void	add_sphere(t_world *world, const t_vector3 *center, double radius, int color);
void	add_plane(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color);
void	add_cylinder(t_world *world, const t_vector3 *point, const t_vector3 *normal, int color, double radius, double height);

int		init_world_and_camera(t_world *world, t_camera *camera);

#endif
