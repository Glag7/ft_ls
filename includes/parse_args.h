#ifndef PARSE_ARGS_H
# define PARSE_ARGS_H

#include <stddef.h>

int		extract_opts(size_t argc, char **argv, size_t *opts);
size_t	extract_args(size_t argc, char **args);

#endif //PARSE_ARGS_H
