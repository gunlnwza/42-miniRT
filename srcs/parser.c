#include "../includes/mini_rt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int parse_ambient(char **tokens, t_world *world)
{
	int	r;
	int	g;
	int	b;

	if (tokens[1] == NULL || tokens[2] == NULL)
		return (0);
	sscanf(tokens[2], "%d,%d,%d", &r, &g, &b);
	world->ambient_light_color = get_rgba(r, g, b, 255);
	return (0);
}

static int parse_camera(char **tokens, t_camera *camera)
{
	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
		return (0);
	sscanf(tokens[1], "%lf,%lf,%lf", &camera->center.x, &camera->center.y, &camera->center.z);
	sscanf(tokens[2], "%lf,%lf,%lf", &camera->normal.x, &camera->normal.y, &camera->normal.z);
	camera->deg_fov = atoi(tokens[3]);
	return (1);
}

static int parse_light(char **tokens, t_world *world)
{
	t_vector3	point;
	int			r;
	int			g;
	int			b;
	float		brighteness;

	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
		return (0);
	sscanf(tokens[1], "%lf,%lf,%lf", &point.x, &point.y, &point.z);
	brighteness = atof(tokens[2]);
	sscanf(tokens[3], "%d,%d,%d", &r, &g, &b);
	world->light.point = point;
	world->light.color = get_rgba(r, g, b, 255);
	return (1);
}

static int parse_sphere(char **tokens, t_world *world)
{
	t_vector3	center;
	float		diameter;
	int			r;
	int			g;
	int			b;

	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
		return (0);
	sscanf(tokens[1], "%lf,%lf,%lf", &center.x, &center.y, &center.z);
	diameter = atof(tokens[2]);
	sscanf(tokens[3], "%d,%d,%d", &r, &g, &b);
	add_sphere(world, &center, diameter / 2.0, get_rgba(r, g, b, 255));
	return (1);
}

static int parse_plane(char **tokens, t_world *world)
{
	t_vector3	point;
	t_vector3	normal;
	int			r;
	int			g;
	int			b;

	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL)
		return (0);
	sscanf(tokens[1], "%lf,%lf,%lf", &point.x, &point.y, &point.z);
	sscanf(tokens[2], "%lf,%lf,%lf", &normal.x, &normal.y, &normal.z);
	sscanf(tokens[3], "%d,%d,%d", &r, &g, &b);
	add_plane(world, &point, &normal, get_rgba(r, g, b, 255));
	return (1);
}

static int parse_cylinder(char **tokens, t_world *world)
{
	t_vector3	center;
	t_vector3	axis;

	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] == NULL || tokens[4] == NULL || tokens[5] == NULL)
		return (0);
	sscanf(tokens[1], "%lf,%lf,%lf", &center.x, &center.y, &center.z);
	sscanf(tokens[2], "%lf,%lf,%lf", &axis.x, &axis.y, &axis.z);
	float diameter = atof(tokens[3]);
	float height = atof(tokens[4]);
	int r, g, b;
	sscanf(tokens[5], "%d,%d,%d", &r, &g, &b);
	add_cylinder(world, &center, &axis, get_rgba(r, g, b, 255), diameter / 2.0, height);
	return (1);
}

int parse_scene(const char *filename, t_world *world, t_camera *camera)
{
	FILE *file = fopen(filename, "r");
	if (!file) {
		perror("Error opening file");
		return 0;
	}

	char line[256];
	while (fgets(line, sizeof(line), file)) {
		char *tokens[6];
		int i = 0;
		char *token = strtok(line, " \n");
		while (token != NULL && i < 6) {
			tokens[i++] = token;
			token = strtok(NULL, " \n");
		}
		tokens[i] = NULL;

		if (tokens[0] == NULL) continue;

		if (strcmp(tokens[0], "A") == 0) {
			if (!parse_ambient(tokens, world)) {
				fclose(file);
				return 0;
			}
		} else if (strcmp(tokens[0], "C") == 0) {
			if (!parse_camera(tokens, camera)) {
				fclose(file);
				return 0;
			}
		} else if (strcmp(tokens[0], "L") == 0) {
			if (!parse_light(tokens, world)) {
				fclose(file);
				return 0; 
			}
		} else if (strcmp(tokens[0], "sp") == 0) {
			if (!parse_sphere(tokens, world)) {
				fclose(file);
				return 0;
			}
		} else if (strcmp(tokens[0], "pl") == 0) {
			if (!parse_plane(tokens, world)) {
				fclose(file);
				return 0;
			}
		} else if (strcmp(tokens[0], "cy") == 0) {
			if (!parse_cylinder(tokens, world)) {
				fclose(file);
				return 0;
			}
		} else {
			fclose(file);
			return 0; 
		}
	}

	fclose(file);
	return 1;
}
