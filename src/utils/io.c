#include <unistd.h>
#include <stdarg.h>
#include "utils.h"

void	ft_printerr(size_t n, ...)
{
	va_list	args;
	char	*tmp;

	va_start(args, n);
	write(2, "ft_ls: ", 7);
	tmp = va_arg(args, char*);
	write(2, tmp, ft_strlen(tmp));
	if (n == 1)
	{
		write(2, "\n", 1);
		va_end(args);
		return;
	}
	write(2, " '", 2);
	tmp = va_arg(args, char*);
	write(2, tmp, ft_strlen(tmp));
	if (n == 2)
	{
		write(2, "'\n", 2);
		va_end(args);
		return;
	}
	write(2, "': ", 3);
	tmp = va_arg(args, char*);
	write(2, tmp, ft_strlen(tmp));
	write(2, "\n", 1);
	va_end(args);
}
