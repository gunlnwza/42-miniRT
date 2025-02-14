#include "../../includes/vector3.h"

t_vector3	v_proj(const t_vector3 *vec, const t_vector3 *onto)
{
    t_vector3	parallel_component;

    v_copy(&parallel_component, onto);
    v_scalar_mul(&parallel_component, v_dot(vec, onto));
    return (parallel_component);
}

t_vector3	v_rej(const t_vector3 *vec, const t_vector3 *onto)
{
    t_vector3   parallel_component;
    t_vector3   perpendicular_component;

    parallel_component = v_proj(vec, onto);
    v_copy(&perpendicular_component, vec);
    v_sub(&perpendicular_component, &parallel_component);
    return (perpendicular_component);
}
