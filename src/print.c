#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "opts.h"
#include "fileinfo.h"
#include "utils.h"

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
