#ifndef HIT_RECORD_H
# define HIT_RECORD_H

# include "vector3.h"

typedef struct s_hit_record
{
	t_vector3	point;
	t_vector3	normal;
	float		t;
	int			color;
}	t_hit_record;

#endif
