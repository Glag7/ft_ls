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
#include "manage_finfo.h"
#include "print.h"

void	append_filename(char *path, size_t pathlen, char *filename)
{
	if (path[pathlen - 1] != '/')
		path[pathlen++] = '/';
	ft_memcpy(path + pathlen, filename, ft_strlen(filename) + 1);
}

static finfo_t	*get_dir(char *path, size_t pathlen, const fopts_t *opts, size_t *nfile_ptr)
{
	size_t			maxfiles = get_finfo_buf_size();
	finfo_t			*files = get_finfo_buf(maxfiles);
	size_t			nfiles = 0;
	DIR*			dir = opendir(path);
	struct dirent	*file;

	if (dir == NULL)
	{
		ft_printerr(3, "cannot open directory", path, strerror(errno));
		*nfile_ptr = -1ULL;
		return NULL;
	}
	file = readdir(dir);
	while (file)
	{
		if (opts->hidden || file->d_name[0] != '.')
		{
			int	ret;

			if (nfiles >= maxfiles)
			{
				maxfiles = (maxfiles) ? maxfiles * 2 : 2;
				files = get_finfo_buf(maxfiles);
				if (files == NULL)
				{
					nfiles = -1ULL;
					break;
				}
			}
			append_filename(path, pathlen, file->d_name);
			ret = fill_finfo(path, file->d_name, opts, files + nfiles++);
			path[pathlen] = '\0';
			if (ret == 2 && nfiles)
				--nfiles;
		}
		file = readdir(dir);
	}
	closedir(dir);
	*nfile_ptr = nfiles;
	return files;
}

static inline void	printpath(char *path, size_t pathlen)
{
	path[pathlen] = ':';
	path[pathlen + 1] = '\n';
	write(1, path, pathlen + 2);
	path[pathlen] = '\0';
}

int	list_subdir_entries(char *path, size_t pathlen, const fopts_t *fopts, const dopts_t *dopts,
	size_t offset)
{
	size_t	nfile = 0;
	finfo_t	*finfos = get_dir(path, pathlen, fopts, &nfile);
	finfo_t	**finfos_ptr;
	dinfo_t	max_dinfo = {0};
	int		err = 0;

	if (nfile == -1ULL)
	{
		if (errno == ENOMEM)
			return 4;
		return 1;
	}
	finfos_ptr = get_finfoptr_buf(nfile);
	if (finfos_ptr == NULL)
		return 4;
	printpath(path, pathlen);
	for (size_t i = 0; i < nfile; ++i)
	{
		finfos_ptr[i] = finfos + i;
		update_dinfo(&max_dinfo, &finfos[i].dinfo);
	}
	if (dopts->cmpfunc)
		ft_qsort_ptr(finfos_ptr, nfile, dopts->cmpfunc);
	print_finfo(path, pathlen, finfos_ptr, nfile, dopts, &max_dinfo);
	for (size_t i = 0; i < nfile; ++i)
	{
		if (!finfos_ptr[i]->isdir)
			continue;
		append_filename(path, pathlen, finfos_ptr[i]->name);
		write(1, "\n", 1);
		set_buf_offset(offset + nfile);
		err |= list_subdir_entries(path, pathlen + finfos_ptr[i]->dinfo.namelen + 1, fopts, dopts,
								offset + nfile);
		set_buf_offset(offset);
		finfos_ptr = get_finfoptr_buf(nfile);
		path[pathlen] = '\0';
		if (err & 4)
			break;
	}
	if (err & 4)
		return 4;
	return err & 1;
}

int	list_dir_entries(char *path, size_t pathlen, const fopts_t *fopts, const dopts_t *dopts,
	bool print_path, bool recursive)
{
	size_t	nfile = 0;
	finfo_t	*finfos = get_dir(path, pathlen, fopts, &nfile);
	finfo_t	**finfos_ptr;
	dinfo_t	max_dinfo = {0};
	int		err = 0;

	if (nfile == -1ULL)
	{
		if (errno == ENOMEM)
			return 4;
		return 2;
	}
	finfos_ptr = get_finfoptr_buf(nfile);
	if (finfos_ptr == NULL)
		return 4;
	if (print_path)
		printpath(path, pathlen);
	for (size_t i = 0; i < nfile; ++i)
	{
		finfos_ptr[i] = finfos + i;
		if (!print_path && recursive && finfos[i].isdir)
		{
			print_path = true;
			printpath(path, pathlen);
		}
		update_dinfo(&max_dinfo, &finfos[i].dinfo);
	}
	if (dopts->cmpfunc)
		ft_qsort_ptr(finfos_ptr, nfile, dopts->cmpfunc);
	print_finfo(path, pathlen, finfos_ptr, nfile, dopts, &max_dinfo);
	if (!recursive)
		return 0;
	for (size_t i = 0; i < nfile; ++i)
	{
		if (!finfos_ptr[i]->isdir)
			continue;
		append_filename(path, pathlen, finfos_ptr[i]->name);
		write(1, "\n", 1);
		set_buf_offset(nfile);
		err |= list_subdir_entries(path, pathlen + finfos_ptr[i]->dinfo.namelen + 1, fopts, dopts,
								nfile);
		set_buf_offset(0);
		finfos_ptr = get_finfoptr_buf(nfile);
		path[pathlen] = '\0';
		if (err & 4)
			break;
	}
	set_buf_offset(0);
	if (err & 4)
		return 4;
	return err & 1;
}
