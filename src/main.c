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

#include "opts.h"

void	fill_file_opts(const size_t *opts, fopts_t *file_opts)
{
	file_opts->hidden = opts['a'];
	file_opts->data = opts['l'] || opts['g'] || opts['o'];
	file_opts->owner = (opts['l'] || opts['o']) && !opts['g'];
	file_opts->group = (opts['l'] || opts['g']) && !opts['o'];
	file_opts->lastmod = opts['l'] || opts['g'] || opts['o'] || opts['t'];
	file_opts->dir_as_file = opts['d'];
}

#include "cmp.h"
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

#include <string.h>
#include "utils.h"
#include "fileinfo.h"
#include <sys/stat.h>

int	fill_finfo(const char *path, char *name, const fopts_t *opts, finfo_t *finfo)
{
	struct stat	buf;

	finfo->name = name;
	finfo->isdir = false;
	finfo->group = (gid_t)-1;
	finfo->owner = (uid_t)-1;
	finfo->nlinks = (nlink_t)-1;
	finfo->size = (off_t)-1;
	finfo->symlink = false;
	finfo->perms = (mode_t)-1;
	finfo->lastmod.tv_sec = (long)-1;
	finfo->lastmod.tv_nsec = (long)-1;
	errno = 0;
	if (lstat(path, &buf))
	{
		ft_printerr(3, "cannot get info for file", name, strerror(errno));
		return -1;
	}
	if (opts->owner)
		finfo->owner = buf.st_uid;
	if (opts->group)
		finfo->group = buf.st_gid;
	if (opts->data)
	{
		finfo->nlinks = buf.st_nlink;
		finfo->size = buf.st_size;
		if (S_ISLNK(buf.st_mode))
			finfo->symlink = true;
		finfo->perms = buf.st_mode;
	}
	if (opts->lastmod)
		finfo->lastmod = buf.st_mtim;
	if (!opts->dir_as_file && S_ISDIR(buf.st_mode))
		finfo->isdir = true;
	return 0;
}

//TODO ACL
void	print_finfo(finfo_t	*finfos, const dopts_t *dopts)
{
	//si columns total
	//toujours en 1 seule colonne lol
	//sort
	//sticky bit de merde, set uid, set gid ??
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
	fill_display_opts(opts, &dopts);

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
		struct stat	wow;

		lstat(args[i], &wow);
		printf("%llu\n", wow.st_size);
	}
	

	return 0;
}
