#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "manage_finfo.h"
#include "parse_args.h"
#include "opts.h"
#include "fileinfo.h"
#include "manage_buf.h"
#include "print.h"
#include "utils.h"
#include "manage_dir.h"

static int	list_dirs(finfo_t *dirs, size_t ndirs, const fopts_t *fopts, const dopts_t *dopts,
					bool recursive)
{
	static char	path[262144];
	finfo_t		**dir_ptr = malloc(ndirs * sizeof(finfo_t *));
	int			err = 0;

	if (dir_ptr == NULL)
	{
		ft_printerr(2, "malloc failed", strerror(errno));
		return 2;
	}
	for (size_t i = 0; i < ndirs; ++i)
		dir_ptr[i] = dirs + i;
	if (dopts->cmpfunc)
		ft_qsort_ptr(dir_ptr, ndirs, dopts->cmpfunc);
	for (size_t i = 0; i < ndirs; ++i)
	{
		size_t	len = ft_strlen(dir_ptr[i]->name);

		ft_memcpy(path, dir_ptr[i]->name, len + 1);
		err |= list_dir_entries(path, len, fopts, dopts, ndirs > 1 || recursive, recursive);
		if (err & 4)//malloc error yes i should use a macro
			break;
		if (i != ndirs - 1)
			write(1, "\n", 1);
	}
	free(dir_ptr);
	if (err >= 2)
		return 2;
	return err & 1;
}

static int	list_args(char **args, size_t nargs, const fopts_t *fopts, const dopts_t *dopts,
					bool recursive)
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
		if (dirs[ndirs].isdir && (!dopts->columns || !dirs[ndirs].symlink))
			ndirs++;
		else
			files[nfiles++] = dirs[ndirs];
	}
	if (nfiles)
		ret = print_finfo_args(files, nfiles, fopts, dopts);
	if (ret != 2)
	{
		err |= ret;
		if (ndirs)
			err |= list_dirs(dirs, ndirs, fopts, dopts, recursive);
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
