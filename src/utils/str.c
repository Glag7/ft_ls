#include <stddef.h>
#include <sys/types.h>

size_t	ft_strlen(const char *s)
{
	size_t	size = 0;

	while (s[size])
		++size;
	return size;
}

ssize_t	ft_at(const char *s, char c)
{
	ssize_t	size = 0;

	while (s[size])
	{
		if (s[size] == c)
			return size;
		++size;
	}
	return -1;
}
