#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include "utils.h"
#include "opts.h"
#include "fileinfo.h"

static inline char	check_acl(const char *path)
{
	acl_t		acl = acl_get_file(path, ACL_TYPE_ACCESS);
	acl_entry_t	entry;
	char		c = '\0';

	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) == 1)
	{
		size_t	i = 1;

		while (acl_get_entry(acl, ACL_NEXT_ENTRY, &entry) == 1)
		{
			++i;
			if (i <= 3)
				continue;
			c = '+';
			break;
		}
	}
	acl_free(acl);
	return c;
}

static void	fill_perms(const char *path, char *perms, mode_t mode)
{
	switch (mode & S_IFMT)
	{
		case S_IFLNK:
			perms[0] = 'l';
			break;
		case S_IFSOCK:
			perms[0] = 's';
			break;
		case S_IFIFO:
			perms[0] = 'p';
			break;
		case S_IFCHR:
			perms[0] = 'c';
			break;
		case S_IFBLK:
			perms[0] = 'b';
			break;
		case S_IFDIR:
			perms[0] = 'd';
			break;
		default:
			perms[0] = '-';
			break;
	}
	perms[1] = (mode & S_IRUSR) ? 'r' : '-';
	perms[2] = (mode & S_IWUSR) ? 'w' : '-';
	perms[3] = (mode & S_ISUID) ? 's' : ((mode & S_IXUSR) ? 'x' : '-');
	perms[4] = (mode & S_IRGRP) ? 'r' : '-';
	perms[5] = (mode & S_IWGRP) ? 'w' : '-';
	perms[6] = (mode & S_ISGID) ? 's' : ((mode & S_IXGRP) ? 'x' : '-');
	perms[7] = (mode & S_IROTH) ? 'r' : '-';
	perms[8] = (mode & S_IWOTH) ? 'w' : '-';
	perms[9] = (mode & S_ISVTX) ? 't' : ((mode & S_IXOTH) ? 'x' : '-');
	perms[10] = check_acl(path);
	perms[11] = '\0';
}

static int	fill_owner(char *buf, uid_t owner, char *filename)
{
	struct passwd	*user;

	errno = 0;
	user = getpwuid(owner);
	if (user == NULL)
	{
		buf[0] = '\0';
		ft_printerr(3, "cannot access owner for", filename, strerror(errno));
		return 1;
	}
	ft_memcpy(buf, user->pw_name, ft_strlen(user->pw_name) + 1);
	return 0;
}

static int	fill_group(char *buf, gid_t group, char *filename)
{
	struct group	*grp_struct;
	
	errno = 0;
	grp_struct = getgrgid(group);
	if (grp_struct == NULL)
	{
		buf[0] = '\0';
		ft_printerr(3, "cannot access owner for", filename, strerror(errno));
		return 1;
	}
	ft_memcpy(buf, grp_struct->gr_name, ft_strlen(grp_struct->gr_name) + 1);
	return 0;
}

static void	fill_dinfo(finfo_t *finfo, dinfo_t *dinfo)
{
	dinfo->permlen = ft_strlen(finfo->perms);
	dinfo->nlinklen = ft_numlen(finfo->nlinks);
	dinfo->userlen = ft_strlen(finfo->owner);
	dinfo->grouplen = ft_strlen(finfo->group);
	dinfo->sizelen = ft_numlen(finfo->size);
	dinfo->namelen = ft_strlen(finfo->name);
}

int	fill_finfo(const char *path, char *name, const fopts_t *opts, finfo_t *finfo)
{
	struct stat	buf;
	int			err = 0;

	finfo->name = name;
	finfo->perms[0] = 0;
	finfo->isdir = false;
	finfo->group[0] = 0;
	finfo->owner[0] = 0;
	finfo->nlinks = (nlink_t)-1;
	finfo->size = (off_t)-1;
	finfo->symlink = false;
	finfo->lastmod.tv_sec = (long)-1;
	finfo->lastmod.tv_nsec = (long)-1;
	errno = 0;
	if (lstat(path, &buf))
	{
		ft_printerr(3, "cannot get info for file", name, strerror(errno));
		return 2;
	}
	if (opts->owner)
		err |= fill_owner(finfo->owner, buf.st_uid, name);
	if (opts->group)
		err |= fill_group(finfo->group, buf.st_gid, name);
	if (opts->data)
	{
		finfo->nlinks = buf.st_nlink;
		finfo->size = buf.st_size;
		if (S_ISLNK(buf.st_mode))
			finfo->symlink = true;
		fill_perms(path, finfo->perms, buf.st_mode);
	}
	if (opts->lastmod)
		finfo->lastmod = buf.st_mtim;
	if (!opts->dir_as_file && S_ISDIR(buf.st_mode))
		finfo->isdir = true;
	fill_dinfo(finfo, &finfo->dinfo);
	return err;
}

void	update_dinfo(dinfo_t *max_dinfo, const dinfo_t *file_dinfo)
{
	if (file_dinfo->permlen > max_dinfo->permlen)
		max_dinfo->permlen = file_dinfo->permlen;
	if (file_dinfo->nlinklen > max_dinfo->nlinklen)
		max_dinfo->nlinklen = file_dinfo->nlinklen;
	if (file_dinfo->userlen > max_dinfo->userlen)
		max_dinfo->userlen = file_dinfo->userlen;
	if (file_dinfo->grouplen > max_dinfo->grouplen)
		max_dinfo->grouplen = file_dinfo->grouplen;
	if (file_dinfo->sizelen > max_dinfo->sizelen)
		max_dinfo->sizelen = file_dinfo->sizelen;
	if (file_dinfo->namelen > max_dinfo->namelen)
		max_dinfo->namelen = file_dinfo->namelen;
}
