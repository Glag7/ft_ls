#include "parse_args.h"

/*struct :
recursive bool

list directories bool (overrides recursive)(not really since it does not trigger)

show owner
shwo every other data

sort, funcptr, strcmp, sort by time or do not sort
reverse sort bool

hidden files bool

human sizes bool
*/

//check ls -d .

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

void	list_files(const char *dirname)
{
	DIR*	dir = opendir(dirname);
	struct dirent	*file;

	if (dir == NULL)
		return;//errno
	errno = 0;
	file = readdir(dir);
	while (file)
	{
		printf("//%s\n", file->d_name);
		errno = 0;
		file = readdir(dir);
	}
	if (errno)
		return;//error
	return;
}

typedef struct fopts_s
{
	bool	hidden;
	bool	owner;
	bool	data;
	bool	dir_as_file;
}	fopts_t;

typedef struct	finfo_s
{
	char				*name;
	bool				isdir;
	gid_t				group;
	uid_t				owner;
	nlink_t				nlinks;
	off_t				size;
	bool				symlink;
	mode_t				perms;
	struct timespec		lastmod;
}	finfo_t;

finfo_t	*get_dir(const char *dirname, const fopts_t *opts)
{
	finfo_t			*files = NULL;
	size_t			nfiles = 0;
	DIR*			dir = opendir(dirname);
	struct dirent	*file;

	if (dir == NULL)
		return;//errno
	errno = 0;
	file = readdir(dir);
	while (file)
	{
		//check malloc size for realloc, null at the end
		//fill file data
		errno = 0;
		file = readdir(dir);
	}
	if (errno)
		return;//error
	return;
}

//XXX store data like size etc for printing
//print_dir:
//get files with x data (hidden)
//sort them
//print everything (if -R stop printing to call print_dir again)
//

void	fill_file_opts(const char *opts, fopts_t *file_opts)
{
	file_opts->hidden = opts['a'];
	file_opts->data = opts['l'] || opts['g'];
	file_opts->owner = opts['l'] && !opts['g'];
	file_opts->dir_as_file = opts['d'];
}

int	main(int argc, char **argv)
{
	char	**args = argv;
	char	opts[255] = {0};
	int		err;

	fopts_t	fopts;

	err = extract_opts(argc, argv, opts);
	if (err)
		return err;
	extract_args(argc, args);

	fill_file_opts(opts, &fopts);
	//fill some struct with opts
	//list, sort, format, print
	
	//XXX
	printf("opts\n");
	for (int i = 0; i < 255; ++i)
	{
		if (opts[i])
			printf("%c\n", i);
	}
	printf("args\n");
	for (int i = 0; args[i]; ++i)
	{
		printf("%s\n", args[i]);
	}
	list_files(*args);
	return 0;
}
