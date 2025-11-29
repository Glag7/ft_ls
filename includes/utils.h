#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>
#include <sys/types.h>

//str
size_t	ft_strlen(const char *s);
ssize_t	ft_at(const char *s, char c);

//num
size_t	ft_numlen(size_t num);
void	ft_fillnum(char *s, size_t num, size_t numlen);

//mem
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

//io
void	ft_printerr(size_t n, ...);

//sort
void	ft_qsort_ptr(void *arr_void, size_t count, ssize_t (*cmpfunc)(const void*, const void*));

#endif //UTILS_H
