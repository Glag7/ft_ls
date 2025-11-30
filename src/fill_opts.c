#include <stddef.h>
#include "opts.h"
#include "cmp.h"

void	fill_file_opts(const size_t *opts, fopts_t *file_opts)
{
	file_opts->hidden = opts['a'];
	file_opts->data = opts['l'] || opts['g'] || opts['o'];
	file_opts->owner = (opts['l'] || opts['o']) && !opts['g'];
	file_opts->group = (opts['l'] || opts['g']) && !opts['o'];
	file_opts->lastmod = opts['l'] || opts['g'] || opts['o'] || opts['t'];
	file_opts->dir_as_file = opts['d'];
}

void	fill_display_opts(const size_t *opts, dopts_t *display_opts)
{
	display_opts->humansize = opts['h'];
	display_opts->columns = opts['l'] || opts['g'] || opts['o'];
	if (opts['r'])
	{
		if (opts['t'])
			display_opts->cmpfunc = rcmptime;
		else
			display_opts->cmpfunc = rcmpname;
	}
	else
	{
		if (opts['t'])
			display_opts->cmpfunc = cmptime;
		else
			display_opts->cmpfunc = cmpname;
	}
	if (opts['U'] > opts['t'])
		display_opts->cmpfunc = NULL;
}

