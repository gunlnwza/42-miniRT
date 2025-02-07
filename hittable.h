#ifndef HITTABLE_H
# define HITTABLE_H

# include "sphere.h"

// typedef struct s_hittable
// {
// 	int	(*hit)(t_hittable *hittable, const t_ray *ray, float ray_tmin, float ray_tmax, t_hit_record *rec);

// }	t_hittable;

typedef struct s_hittable
{
	int	(*hit)(t_hittable *, const t_ray *, float, float, t_hit_record *);

}	t_hittable;


#endif
