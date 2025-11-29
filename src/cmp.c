#include <sys/types.h>
#include "utils.h"
#include "fileinfo.h"

ssize_t cmpname(const void *a, const void *b)
{
	const char	*sa = ((finfo_t *)a)->name;
	const char	*sb = ((finfo_t *)b)->name;
	size_t		i = 0;
	
	while (sa[i] && sb[i] && sa[i] == sb[i])
		++i;
	return sa[i] - sb[i];
}

ssize_t rcmpname(const void *a, const void *b)
{
	return cmpname(b, a);
}

ssize_t cmptime(const void *a, const void *b)
{
	const struct timespec	timea = ((finfo_t *)a)->lastmod;
	const struct timespec	timeb = ((finfo_t *)b)->lastmod;

	if (timea.tv_sec != timeb.tv_sec)
		return timea.tv_sec - timeb.tv_sec;
	return timea.tv_nsec - timeb.tv_nsec;
}

ssize_t rcmptime(const void *a, const void *b)
{
	return cmptime(b, a);
}
