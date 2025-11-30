#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "manage_finfo.h"
#include "parse_args.h"
#include "opts.h"
#include "fileinfo.h"
#include "manage_buf.h"
#include "print.h"
#include "utils.h"

//return 2 if dir cant be opened (make a func list subdirs that returns 1)
int	list_dirs(bool recursive)
{
//	static char	path[262144];
	//	print_finfo(files, i, &dopts, &max_dinfo);
//	if (dopts->cmpfunc)
//		ft_qsort_ptr(files_ptr, , dopts->cmpfunc);
	return 0;
}

int	list_args(char **args, size_t nargs, const fopts_t *fopts, const dopts_t *dopts, bool recursive)
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
		ret = print_finfo_args(files, nfiles, fopts, dopts);
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
	int			ret;

	if (extract_opts(argc, argv, opts))
		return 2;
	nargs = extract_args(argc, args);
	fill_file_opts(opts, &fopts);
	fill_display_opts(opts, &dopts);
	ret = list_args(args, nargs, &fopts, &dopts, opts['R']);
	get_finfo_buf(0);
	get_finfoptr_buf(0);
	return ret;
}
