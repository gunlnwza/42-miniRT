#ifndef OBJECT_H
# define OBJECT_H

# include "ray.h"
# include "hit_record.h"
# include "constants.h"

typedef enum e_object_type
{
    SPHERE,
    PLANE,
    CYLINDER,
}   t_object_type;

typedef struct s_object
{
    t_object_type   type;   // sp, pl, cy
    t_vector3       point;  // sp, pl, cy
    int             color;  // sp, pl, cy
    t_vector3       normal; //     pl, cy
    double          radius; // sp,     cy
    double          height; //         cy
}   t_object;

t_object	*create_sphere(const t_vector3 *center, double radius, int color);
int			hit_sphere(t_object *sphere, const t_ray *ray, t_hit_record *rec);

t_object    *create_plane(const t_vector3 *point, const t_vector3 *normal, int color);
int         hit_plane(t_object *plane, const t_ray *ray, t_hit_record *rec);

t_object    *create_cylinder(const t_vector3 *point, double radius, const t_vector3 *normal, int color, double height);
int         hit_cylinder(t_object *cylinder, const t_ray *ray, t_hit_record *rec);


#endif
