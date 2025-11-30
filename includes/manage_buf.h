#ifndef MANAGE_BUF_H
# define MANAGE_BUF_H

#include <stddef.h>
#include "fileinfo.h"

finfo_t	*get_finfo_buf(size_t size);
finfo_t	**get_finfoptr_buf(size_t size);

#endif //MANAGE_BUF_H
