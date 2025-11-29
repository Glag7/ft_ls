#include <stdint.h>
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src_c;
	char	*dest_c;
	uint64_t	*src_long;
	uint64_t	*dest_long;
	size_t	i;

	i = 0;
	src_c = (char *)src;
	dest_c = (char *)dest;
	src_long = (uint64_t *)src;
	dest_long = (uint64_t *)dest;
	while (i < n / sizeof(size_t))
	{
		dest_long[i] = src_long[i];
		i++;
	}
	i *= sizeof(uint64_t);
	while (i < n)
	{
		dest_c[i] = src_c[i];
		i++;
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	uint64_t			*ptr_long;
	uint64_t			cons;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	c = (unsigned char) c;
	cons = c;
	cons = cons | (cons << 8) | (cons << 16) | (cons << 24)
			| (cons << 32) | (cons << 40) | (cons << 48) | (cons << 56);
	ptr = (unsigned char *) s;
	ptr_long = (uint64_t *) s;
	while (i < n / sizeof(uint64_t))
	{
		ptr_long[i] = cons;
		i++;
	}
	i *= sizeof(uint64_t);
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	return (s);
}
