#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include "utils.h"
#include "opts.h"
#include "fileinfo.h"

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
