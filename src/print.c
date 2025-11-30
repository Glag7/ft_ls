#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include "opts.h"
#include "fileinfo.h"
#include "manage_finfo.h"
#include "utils.h"

static void	print_line(const char *path, finfo_t *finfo,
						const dopts_t *dopts, const dinfo_t *max_dinfo)
{	
	static char		buf[262144];
	const dinfo_t	*file_dinfo = &finfo->dinfo;
	size_t			i = 0;
	
	if (dopts->columns)
	{
		ft_memset(buf, ' ', max_dinfo->permlen + max_dinfo->nlinklen + max_dinfo->userlen
							+ max_dinfo->grouplen + max_dinfo->sizelen + max_dinfo->namelen + 20);
		ft_memcpy(buf + i, finfo->perms, file_dinfo->permlen);
		i += max_dinfo->permlen + 1;
		i += max_dinfo->nlinklen - file_dinfo->nlinklen;
		ft_fillnum(buf + i, finfo->nlinks, file_dinfo->nlinklen);
		i += file_dinfo->nlinklen + 1;
		if (max_dinfo->userlen)
		{
			ft_memcpy(buf + i, finfo->owner, file_dinfo->userlen);
			i += max_dinfo->userlen + 1;
		}
		if (max_dinfo->grouplen)
		{
			ft_memcpy(buf + i, finfo->group, file_dinfo->grouplen);
			i += max_dinfo->grouplen + 1;
		}
		i += max_dinfo->sizelen - file_dinfo->sizelen;
		if (dopts->humansize)
			ft_fillnum_human(buf + i, finfo->size, file_dinfo->sizelen);
		else
			ft_fillnum(buf + i, finfo->size, file_dinfo->sizelen);
		i += file_dinfo->sizelen + 1;
		
		char 	*date = ctime(&finfo->lastmod.tv_sec);
		size_t	len = ft_strlen(date) - 13;

		ft_memcpy(buf + i, date + 4, len);
		i += len + 1;
	}
	ft_memcpy(buf + i, finfo->name, file_dinfo->namelen);
	i += file_dinfo->namelen;
	if (dopts->columns && finfo->symlink)
	{
		ssize_t	res = readlink(path, buf + i + 4, sizeof(buf) - i);
		
		if (res == -1)
			ft_printerr(3, "cannot get symlink", path, strerror(errno));
		else
		{
			buf[i + 1] = '-';
			buf[i + 2] = '>';
			i += 4 + res;
		}
	}
	buf[i] = '\n';
	write(1, buf, i + 1);
}

int	print_finfo_args(finfo_t *files, size_t nfiles, const fopts_t *fopts, const dopts_t *dopts)
{
	dinfo_t		max_dinfo = {0};
	finfo_t		**files_ptr = malloc(nfiles * sizeof(finfo_t *));
	int			err = 0;

	if (files_ptr == NULL)
		return 2;
	for (size_t i = 0; i < nfiles; ++i)
	{
		files_ptr[i] = files + i;
		err |= fill_finfo(files[i].name, files[i].name, fopts, files + i);
		update_dinfo(&max_dinfo, &files[i].dinfo);
	}
	if (dopts->cmpfunc)
		ft_qsort_ptr(files_ptr, nfiles, dopts->cmpfunc);
	for (size_t i = 0; i < nfiles; ++i)
		print_line(files_ptr[i]->name, files_ptr[i], dopts, &max_dinfo);
	free(files_ptr);
	return err;
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
		print_line("", finfos_ptr[i], dopts, max_dinfo);
	}
	free(finfos_ptr);
	return 0;
}
