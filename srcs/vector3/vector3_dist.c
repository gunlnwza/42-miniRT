#include "../../includes/vector3.h"

double	v_dist2(const t_vector3 *a, const t_vector3 *b)
{
	t_vector3	diff;

	diff = v_sub(b, a);
	return (v_norm2(&diff));
}

double	v_dist(const t_vector3 *a, const t_vector3 *b)
{
	return (sqrt(v_dist2(a, b)));
}
