#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>
#include <sys/types.h>

//str
size_t	ft_strlen(const char *s);
ssize_t	ft_at(const char *s, char c);

//mem
void	*ft_memcpy(void * dest, const void *src, size_t n);

//io
void	ft_printerr(size_t n, ...);

#endif //UTILS_H
