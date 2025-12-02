#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "fileinfo.h"
#include "utils.h"

struct finfo_buf
{
	finfo_t	*finfo_buf;
	finfo_t	**finfoptr_buf;
	size_t	finfo_size;
	size_t	finfoptr_size;
};

static struct finfo_buf	*getstruct()
{
	static struct finfo_buf	buffers = {0};

	return &buffers;
}

size_t	get_finfo_buf_size()
{
	struct finfo_buf	*fbuf = getstruct();

	return fbuf->finfo_size;
}

size_t	get_finfoptr_buf_size()
{
	struct finfo_buf	*fbuf = getstruct();

	return fbuf->finfoptr_size;
}

finfo_t	*get_finfo_buf(size_t size)
{
	struct finfo_buf	*fbuf = getstruct();
	finfo_t				*tmp;

	if (size == 0)
	{
		free(fbuf->finfo_buf);
		fbuf->finfo_buf = NULL;
		fbuf->finfo_size = 0;
	}
	if (fbuf->finfo_size >= size)
		return fbuf->finfo_buf;
	tmp = malloc(size * sizeof(finfo_t));
	if (tmp == NULL)
	{
		ft_printerr(2, "malloc failed", strerror(errno));
		free(fbuf->finfo_buf);
		fbuf->finfo_buf = NULL;
		fbuf->finfo_size = 0;
	}
	else
	{
		//change_ptr
		printf("wtf\n");
		for (size_t i = 0; i < fbuf->finfoptr_size; ++i)
		{
			printf("INDEX IS %llu\n", fbuf->finfoptr_buf[i] - tmp);
		}
		ft_memcpy(tmp, fbuf->finfo_buf, fbuf->finfo_size * sizeof(finfo_t));
		free(fbuf->finfo_buf);
		fbuf->finfo_buf = tmp;
		fbuf->finfo_size = size;
	}
	return fbuf->finfo_buf;
}

finfo_t	**get_finfoptr_buf(size_t size)
{
	printf("HELLO\n");
	struct finfo_buf	*fbuf = getstruct();
	finfo_t				**tmp;

	if (size == 0)
	{
		free(fbuf->finfoptr_buf);
		fbuf->finfoptr_buf = NULL;
		fbuf->finfoptr_size = 0;
	}
	if (fbuf->finfoptr_size >= size)
		return fbuf->finfoptr_buf;
	tmp = malloc(size * sizeof(finfo_t *));
	if (tmp == NULL)
	{
		ft_printerr(2, "malloc failed", strerror(errno));
		free(fbuf->finfoptr_buf);
		fbuf->finfoptr_buf = NULL;
		fbuf->finfoptr_size = 0;
	}
	else
	{
		ft_memcpy(tmp, fbuf->finfoptr_buf, fbuf->finfoptr_size * sizeof(finfo_t *));
		free(fbuf->finfoptr_buf);
		fbuf->finfoptr_buf = tmp;
		fbuf->finfoptr_size = size;
	}
	return fbuf->finfoptr_buf;
}
