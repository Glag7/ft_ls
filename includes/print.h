#ifndef PRINT_H
# define PRINT_H

#include "opts.h"
#include "fileinfo.h"

int	print_finfo_args(finfo_t *files, size_t nfiles, const fopts_t *fopts, const dopts_t *dopts);
int	print_finfo(char *path, size_t pathlen, finfo_t	**finfos_ptr, size_t n, const dopts_t *dopts,
			const dinfo_t *max_dinfo);

#endif
