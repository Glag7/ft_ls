#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include "fileinfo.h"
#include "utils.h"

finfo_t	*get_finfo_buf(size_t size)
{
	static finfo_t	*buf = NULL;
	static size_t	cursize = 0;
	finfo_t			*tmp;

	if (size == 0)
	{
		free(buf);
		buf = NULL;
		cursize = 0;
	}
	if (cursize <= size)
		return buf;
	tmp = malloc(size * sizeof(finfo_t));
	if (tmp == NULL)
	{
		ft_printerr(2, "malloc failed", strerror(errno));
		free(buf);
		buf = NULL;
		cursize = 0;
	}
	else
	{
		ft_memcpy(tmp, buf, cursize);
		free(buf);
		buf = tmp;
		cursize = size;
	}
	return buf;
}

finfo_t	**get_finfoptr_buf(size_t size)
{
	static finfo_t	**buf = NULL;
	static size_t	cursize = 0;
	finfo_t			**tmp;

	if (size == 0)
	{
		free(buf);
		buf = NULL;
		cursize = 0;
	}
	if (cursize <= size)
		return buf;
	tmp = malloc(size * sizeof(finfo_t *));
	if (tmp == NULL)
	{
		ft_printerr(2, "malloc failed", strerror(errno));
		free(buf);
		buf = NULL;
		cursize = 0;
	}
	else
	{
		ft_memcpy(tmp, buf, cursize);
		free(buf);
		buf = tmp;
		cursize = size;
	}
	return buf;
}
