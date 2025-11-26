#ifndef OPTS_H
# define OPTS_H

#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

typedef struct fopts_s
{
	bool	hidden;
	bool	owner;
	bool	data;
	bool	dir_as_file;
}	fopts_t;

typedef struct displayopts_s
{
	ssize_t (*cmpfunc)(const void*, const void*);
	bool	columns;
	bool	humansize;
}	dopts_t;

#endif //OPTS_H
