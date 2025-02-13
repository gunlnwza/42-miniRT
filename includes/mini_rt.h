#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# include "libs.h"
# include "world_and_camera.h"

int parse_scene(const char *filename, t_world *world, t_camera *camera);

#endif
