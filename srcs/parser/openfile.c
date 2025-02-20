#include "../../includes/mini_rt.h"

int read_file(t_world *world, int fd) {
	char *line;
	while ((line = get_next_line(fd)) != NULL) {
		line = sanitize_line(line);
		if (parse_params(world, line) != 0) {
            free(line);
            return show_error("Failed to parse line");
        }
        free(line);
	}
	return (0);
}

int open_file(t_world *world, const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        return show_error("Failed to open file");
    }
	int	result = read_file(world, fd);
    close(fd);
    return (result);
}

char *sanitize_line(char *line) {
	int i = -1;
	char *tmp = ft_strdup(line);
	free(line);
	while (tmp && tmp[++i]) {
		if (tmp[i] == '\t' || tmp[i] == '\n') {
			tmp[i] = ' ';
		}
	}
	char *trimmed_line = ft_strtrim(tmp, " ");
	free(tmp);
	return (trimmed_line);
}
