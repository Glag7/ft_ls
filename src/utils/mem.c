#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src_c;
	char	*dest_c;
	size_t	*src_long;
	size_t	*dest_long;
	size_t	i;

	i = 0;
	src_c = (char *)src;
	dest_c = (char *)dest;
	src_long = (size_t *)src;
	dest_long = (size_t *)dest;
	while (i < n / sizeof(size_t))
	{
		dest_long[i] = src_long[i];
		i++;
	}
	i *= sizeof(size_t);
	while (i < n)
	{
		dest_c[i] = src_c[i];
		i++;
	}
	return (dest);
}
