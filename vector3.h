#ifndef VECTOR3_H
# define VECTOR3_H

# include <stdlib.h>
# include <math.h>

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

t_vector3	*vector3_create(float x, float y, float z);

void		vector3_add_ip(t_vector3 *dest, t_vector3 *src);
void		vector3_sub_ip(t_vector3 *dest, t_vector3 *src);

float		vector3_dot(t_vector3 *dest, t_vector3 *src);

void		vector3_element_mul_ip(t_vector3 *dest, t_vector3 *src);
void		vector3_scalar_mul_ip(t_vector3 *dest, float scalar);
void		vector3_cross_ip(t_vector3 *dest, t_vector3 *src);

float		vector3_norm2(t_vector3 *dest);
float		vector3_norm(t_vector3 *dest);

void		vector3_normalize_ip(t_vector3 *dest);

void		vector3_free(t_vector3 **dest);

#endif
