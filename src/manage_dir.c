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


finfo_t	*get_dir(const char *dirname, const fopts_t *opts)
{
	finfo_t			*files = NULL;
	size_t			nfiles = 0;
	DIR*			dir = opendir(dirname);
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
		//check malloc size for realloc, null at the end
		//fill file data
		errno = 0;
		file = readdir(dir);
	}
	//if (errno)
	//	ft_printerr()
	return files;
}

static inline void	printpath(char *path, size_t pathlen)
{
	path[pathlen] = ':';
	path[pathlen + 1] = '\n';
	write(1, path, pathlen + 2);
	path[pathlen] = '\0';
}

//return 2 if dir cant be opened (make a func list subdirs that returns 1)
int	list_dir_entries(char *path, size_t pathlen, const fopts_t *fopts, const dopts_t *dopts,
	bool print_path, bool recursive)
{
	//open first (might fail)
	if (print_path)
		printpath(path, pathlen);
	return 0;
}
