#ifndef FILEINFO_H
# define FILEINFO_H

#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdbool.h>

typedef struct	displayinfo_s
{
	uint8_t		permlen;
	uint8_t		nlinklen;
	uint8_t		userlen;
	uint8_t		grouplen;
	uint8_t		sizelen;
	uint8_t		namelen;
}	dinfo_t;

typedef struct	finfo_s
{
	char				name[256];
	struct timespec		lastmod;
	nlink_t				nlinks;
	off_t				size;
	blkcnt_t			blocks;
	dinfo_t				dinfo;
	bool				isdir;
	bool				symlink;
	char				group[33];
	char				owner[33];
	char				perms[12];
}	finfo_t;

#endif //FILEINFO_H
