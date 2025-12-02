#ifndef MANAGE_BUF_H
# define MANAGE_BUF_H

#include <stddef.h>
#include "fileinfo.h"

finfo_t	*get_finfo_buf(size_t size);
finfo_t	**get_finfoptr_buf(size_t size);
size_t	get_finfo_buf_size();
size_t	get_finfoptr_buf_size();
void	set_buf_offset(size_t n);

#endif //MANAGE_BUF_H
