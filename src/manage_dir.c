#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "opts.h"
#include "fileinfo.h"
#include "manage_buf.h"

finfo_t	**get_dir(const char *path, const fopts_t *opts)
{
	finfo_t			*files = get_finfo_buf(32);
	size_t			nfiles = 0;
	size_t			maxfiles = 32;
	DIR*			dir = opendir(path);
	struct dirent	*file;

	if (dir == NULL)
	{
		ft_printerr(3, "cannot open directory", strerror(errno));
		return NULL;
	}
	errno = 0;
	file = readdir(dir);
	while (file)
	{
		if (opts->hidden || file->d_name[0] != '.')
		{
		//check malloc size for realloc, null at the end
		//fill file data
		}
		errno = 0;
		file = readdir(dir);
	}
	//if (errno)
	//	ft_printerr()
	closedir(dir);
	return files;
}

static inline void	printpath(char *path, size_t pathlen)
{
	path[pathlen] = ':';
	path[pathlen + 1] = '\n';
	write(1, path, pathlen + 2);
	path[pathlen] = '\0';
}

int	list_dir_entries(char *path, size_t pathlen, const fopts_t *fopts, const dopts_t *dopts,
	bool print_path, bool recursive)
{
	size_t	nfile = 0;
	finfo_t	**finfos = get_dir(path, fopts);
	
	if (finfos == NULL)
	{
		if (errno == ENOMEM)
			return 4;
		return 2;
	}
	for (size_t i = 0; i < nfile; ++i)
	//open first (might fail)
	if (print_path)
		printpath(path, pathlen);
	return 0;
}

//list subdirs that returns 1 ?
