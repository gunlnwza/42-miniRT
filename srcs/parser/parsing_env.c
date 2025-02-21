#include "../../includes/mini_rt.h"

int parse_camera(t_world *world, char **params)
{
    if (array_length(params) != 4)
    {
        free_array(params);
        return (show_error("Invalid camera parameters"));
    }
    parse_vector(params[1], &world->camera.center);
    parse_vector(params[2], &world->camera.normal);
    world->camera.deg_fov = atoi(params[3]);
    free_array(params);
    return (0);
}

int parse_ambient(t_world *world, char **params)
{
    if (array_length(params) != 3)
    {
        free_array(params);
        return (show_error("Invalid ambient parameters"));
    }
    double brightness = atof(params[1]);
    int r, g, b;
    if (sscanf(params[2], "%d,%d,%d", &r, &g, &b) != 3) {
        free_array(params);
        return show_error("Invalid ambient color format");
    }
    world->ambient_light_color = get_rgba((int)(r * brightness), (int)(g * brightness), (int)(b * brightness), 255);
    free_array(params);
    return (0);
}

int parse_light(t_world *world, char **params)
{
    if (array_length(params) != 4)
    {
        free_array(params);
        return (show_error("Invalid light parameters"));
    }
    parse_vector(params[1], &world->light.point);
    float brightness = atof(params[2]);
    int r, g, b;
    if (sscanf(params[3], "%d,%d,%d", &r, &g, &b) != 3) {
        free_array(params);
        return show_error("Invalid light color format");
    }
    world->light.color = get_rgba((int)(r * brightness), (int)(g * brightness), (int)(b * brightness), 255);
    free_array(params);
    return (0);
}
