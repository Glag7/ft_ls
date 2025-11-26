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
#include <stdbool.h>

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

typedef struct displayopts_s
{
	ssize_t (*cmpfunc)(const void*, const void*);
	bool	columns;
	bool	humansize;
}	dopts_t;

/*
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
	if (errno)
		ft_printerr()
	return files;
}
*/
//XXX store data like size etc for printing
//print_dir:
//get files with x data (hidden)
//sort them
//print everything (if -R stop printing to call print_dir again)
//

void	fill_file_opts(const size_t *opts, fopts_t *file_opts)
{
	file_opts->hidden = opts['a'];
	file_opts->data = opts['l'] || opts['g'];
	file_opts->owner = opts['l'] && !opts['g'];
	file_opts->dir_as_file = opts['d'];
}

void	fill_display_opts(const size_t *opts, dopts_t *display_opts)
{
	display_opts->humansize = opts['h'];
	display_opts->columns = opts['l'] || opts['g'];
	if (opts['r'])
	{
		if (opts['t'])
			display_opts->cmpfunc = rcmptime;
		else
			display_opts->cmpfunc = rcmpname;
	}
	else
	{
		if (opts['t'])
			display_opts->cmpfunc = cmptime;
		else
			display_opts->cmpfunc = cmpname;
	}
	if (opts['U'] > opts['t'])
		display_opts->cmpfunc = NULL;
}

int	main(int argc, char **argv)
{
	char	**args = argv;
	size_t	opts[255] = {0};
	int		err;

	fopts_t	fopts;
	dopts_t	dopts;

	err = extract_opts(argc, argv, opts);
	if (err)
		return err;
	extract_args(argc, args);

	fill_file_opts(opts, &fopts);
	fill_display_opts(opts &dopts);

	//sort les args
	//return 2 si un des arsg pas accessibles (pas un dossier)
	//return 1 si erreur mineure (subfolder)

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
	return 0;
}
