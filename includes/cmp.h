#ifndef CMP_H
# define CMP_H

#include <sys/types.h>

ssize_t cmpname(const void *a, const void *b);
ssize_t rcmpname(const void *a, const void *b);
ssize_t cmptime(const void *a, const void *b);
ssize_t rcmptime(const void *a, const void *b);

#endif
