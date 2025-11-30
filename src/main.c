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
	display_opts->columns = opts['l'] || opts['g'] || opts['o'];
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
#include "manage_finfo.h"
#include <sys/stat.h>


#include <stdlib.h>
#include <time.h>

#include <unistd.h>

void	print_line(finfo_t *finfo, const dopts_t *dopts, const dinfo_t *max_dinfo)
{	
	static char		buf[262144];
	const dinfo_t	*file_dinfo = &finfo->dinfo;
	size_t			i = 0;
	
	if (dopts->columns)//kind of useless
	{
		ft_memcpy(buf + i, finfo->perms, file_dinfo->permlen);
		i += file_dinfo->permlen;
		buf[i++] = ' ';//memset with max_dinfo
		ft_fillnum(buf + i, finfo->nlinks, file_dinfo->nlinklen);
		i += file_dinfo->nlinklen;
		buf[i++] = ' ';//XXX
		ft_memcpy(buf + i, finfo->owner, file_dinfo->userlen);
		i += file_dinfo->userlen;//FIXME dont print if 0, same for group
		buf[i++] = ' ';//XXX
		ft_memcpy(buf + i, finfo->group, file_dinfo->grouplen);
		i += file_dinfo->grouplen;
		buf[i++] = ' ';//XXX
		//TODO humansize (doit etre fait avant) (<=4)
		ft_fillnum(buf + i, finfo->size, file_dinfo->sizelen);
		i += file_dinfo->sizelen;
		buf[i++] = ' ';//XXX
		
		char *test = ctime(&finfo->lastmod.tv_sec);//can fail but not really
		size_t	len = ft_strlen(test) - 13;

		ft_memcpy(buf + i, test + 4, len);
		i += len;
		buf[i++] = ' ';//XXX
		//date
	}

	ft_memcpy(buf + i, finfo->name, file_dinfo->namelen);
	i += file_dinfo->namelen;
	if (dopts->columns && finfo->symlink)//XXX maybe ill need the full path
	{
		buf[i++] = ' ';
		buf[i++] = '-';
		buf[i++] = '>';
		buf[i++] = ' ';
		ssize_t	res = readlink(finfo->name, buf + i, sizeof(buf) - i);
		if (res == -1)
		{
			//msg cant follow symlink boohoo
			i -= 4;
		}
		else
			i += res;
	}
	buf[i] = '\n';
	//where \0
	write(1, buf, i + 1);
}
//plusieurs args si dossier mettre le nom

//TODO un seul buffer de fileinfo de malloc, le free a la fin et le realloc si besoin
int	print_finfo(finfo_t	*finfos, size_t n, const dopts_t *dopts, const dinfo_t *max_dinfo)
{
	finfo_t	**finfos_ptr = malloc((n + 1) * sizeof(finfos));

	if (finfos_ptr == NULL)//keep this malloc for the entire program too ? XXX
	{
		ft_printerr(2, "malloc failed", strerror(errno));
		return -1;
	}
	for (size_t i = 0; i < n; ++i)
		finfos_ptr[i] = finfos + i;
	finfos_ptr[n] = NULL;
	if (dopts->cmpfunc)
		ft_qsort_ptr(finfos_ptr, n, dopts->cmpfunc);

	//si columns total
	//toujours en 1 seule colonne lol
	//sort
	//sticky bit de merde, set uid, set gid ??
	for (size_t i = 0; i < n; ++i)
	{
		print_line(finfos_ptr[i], dopts, max_dinfo);
	}
	free(finfos_ptr);
	return 0;
}

//return 2 if dir cant be opened (make a func list subdirs that returns 1)
int	list_dirs(bool recursive)
{
//	static char	path[262144];
	//	print_finfo(files, i, &dopts, &max_dinfo);
//	if (dopts->cmpfunc)
//		ft_qsort_ptr(files_ptr, , dopts->cmpfunc);
	return 0;
}

int	print_finfo_args()
{
//	finfo_t		*files_ptr = malloc(nargs * sizeof(finfo_t *));
//	dinfo_t		max_dinfo = {0};
//
//			//treat as file
//			ret = fill_finfo(args[i], args[i], &fopts, files + i);
//			//update_dinfo(&max_dinfo, &files[i].dinfo);//XXX
//	if (dopts->cmpfunc)
//		ft_qsort_ptr(files_ptr, , dopts->cmpfunc);
}

int	list_args(char **args, size_t nargs, fopts_t *fopts, dopts_t *dopts, bool recursive)
{
	finfo_t		*files = malloc(nargs * sizeof(finfo_t));
	finfo_t		*dirs = malloc(nargs * sizeof(finfo_t));
	size_t		nfiles = 0;
	size_t		ndirs = 0;
	int			err = 0;
	int			ret = 0;

	if (files == NULL || dirs == NULL)
	{
		free(files);
		free(dirs);
		ft_printerr(2, "malloc failed", strerror(errno));
		return 2;
	}
	for (size_t i = 0; i < nargs; ++i)
	{
		if (fill_finfo_arg(args[i], args[i], fopts, dirs + ndirs))
		{
			ft_printerr(2, "cannot access", strerror(errno));
			err = 2;
			continue;
		}
		if (dirs[ndirs].isdir && !(dopts->columns && dirs[ndirs].symlink))
			ndirs++;
		else
			files[nfiles++] = dirs[ndirs];
	}
	if (nfiles)
		ret = print_finfo_args();
	if (ret != 2)
	{
		err |= ret;
		err |= list_dirs(recursive);
	}
	free(files);
	free(dirs);
	if (err & 2)
		return 2;
	return err;
}

int	main(int argc, char **argv)
{
	char		**args = argv;
	size_t		opts[255] = {0};
	size_t		nargs;
	fopts_t		fopts;
	dopts_t		dopts;

	if (extract_opts(argc, argv, opts))
		return 2;
	nargs = extract_args(argc, args);
	fill_file_opts(opts, &fopts);
	fill_display_opts(opts, &dopts);
	return list_args(args, nargs, &fopts, &dopts, opts['R']);
}
