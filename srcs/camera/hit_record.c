#include "../../includes/hit_record.h"

void    hit_record_copy(t_hit_record *dest, const t_hit_record *src)
{
    dest->color = src->color;
    dest->normal = v_copy(&src->normal);
    dest->point = v_copy(&src->point);
    dest->t = src->t;
}
