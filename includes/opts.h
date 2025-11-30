#ifndef OPTS_H
# define OPTS_H

#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

typedef struct fopts_s
{
	bool	hidden;
	bool	owner;
	bool	group;
	bool	lastmod;
	bool	data;
	bool	dir_as_file;
}	fopts_t;

typedef struct displayopts_s
{
	ssize_t (*cmpfunc)(const void*, const void*);
	bool	columns;
	bool	humansize;
}	dopts_t;

void	fill_file_opts(const size_t *opts, fopts_t *file_opts);
void	fill_display_opts(const size_t *opts, dopts_t *display_opts);

#endif //OPTS_H
