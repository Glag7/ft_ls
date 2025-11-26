#ifndef FILEINFO_H
# define FILEINFO_H

#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

typedef struct	finfo_s
{
	char				*name;
	bool				isdir;
	gid_t				group;
	uid_t				owner;
	nlink_t				nlinks;
	off_t				size;
	bool				symlink;
	mode_t				perms;
	struct timespec		lastmod;
}	finfo_t;

#endif //FILEINFO_H
