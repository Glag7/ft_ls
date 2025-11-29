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
#include <sys/stat.h>


#include <stdlib.h>

//date always same type
void	print_line(finfo_t *finfo, const dopts_t *dopts)//paddings ? idk
{
	static char	buf[4096];

	size_t	len = ft_strlen(finfo->name);
	
	if (dopts->columns)
	{
		printf("%s\n", finfo->perms);
	}

	ft_memcpy(buf, finfo->name, len);
	buf[len] = '\n';
	//where \0
	write(1, buf, len + 1);
}

//PADDING
//TODO ACL
//TODO file type (d l p etc)
//d directory
//b block device
//c character device
//l link
//s socket
int	print_finfo(finfo_t	*finfos, size_t n, const dopts_t *dopts)
{
	finfo_t	**finfos_ptr = malloc((n + 1) * sizeof(finfos));

	if (finfos_ptr == NULL)
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
		print_line(finfos_ptr[i], dopts);
	}
	free(finfos_ptr);
	return 0;
}

//TODO un seul buffer de fileinfo de malloc, le free a la fin et le realloc si besoin

#include "manage_finfo.h"

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
	finfo_t	*files = malloc(1000);
	int i;
	for (i = 0; args[i]; ++i)
	{
		files[i].name = args[i];
		fill_finfo(args[i], args[i], &fopts, files + i);//returns 1 if minor error, 2 if no stat
		printf("%s\n", args[i]);
	}
	printf("GRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR\n");
	print_finfo(files, i, &dopts);
	free(files);
	
	printf("%lu %lu\n", sizeof(finfo_t), sizeof(off_t));
	return 0;
}
