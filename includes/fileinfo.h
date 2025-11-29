#ifndef FILEINFO_H
# define FILEINFO_H

#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

typedef struct	finfo_s
{
	char				*name;
	char				perms[12];
	bool				isdir;
	gid_t				group;
	uid_t				owner;
	nlink_t				nlinks;
	off_t				size;
	bool				symlink;
	struct timespec		lastmod;
}	finfo_t;

typedef struct	displayinfo_s
{
	uint8_t		permlen;
	uint8_t		nlinklen;
	uint8_t		userlen;
	uint8_t		grouplen;
	uint8_t		sizelen;
	uint8_t		namelen;
	uint16_t	symlinklen;
}	dinfo_t;

#endif //FILEINFO_H
