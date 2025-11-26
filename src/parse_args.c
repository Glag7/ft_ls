#include <stddef.h>
#include "utils.h"

int	extract_opts(size_t argc, char **argv, size_t *opts)
{
	static const char	accepted[] = "adfghlrRtU";
	size_t				opt_idx = 0;

	for (size_t i = 1; i < argc; ++i)
	{
		const char	*cur = argv[i];

		if (cur[0] != '-')
			continue;
		if (cur[1] == '-' && cur[2] == '\0')
			break;
		for (size_t j = 1; j < ft_strlen(cur); ++j)
		{
			unsigned	c = cur[j];
			if (ft_at(accepted, c) != -1)
				opts[c] = ++opt_idx;
			else
			{
				char	badopt[2] = {c, 0};
				ft_printerr(2, "invalid option --", badopt);
				return 2;
			}
		}
	}
	return 0;
}

void	extract_args(size_t argc, char **args)
{
	static char	default_arg[] = ".";
	size_t		write_idx = 0;
	size_t		read_idx = 1;

	while (read_idx < argc)
	{
		const char	*cur = args[read_idx];

		if (cur[0] == '-')
		{
			if (cur[1] == '-' && cur[2] == '\0')
			{
				++read_idx;
				break;
			}
		}
		else
		{
			args[write_idx] = args[read_idx];
			++write_idx;
		}
		++read_idx;
	}
	if (read_idx - write_idx == argc)
	{
		args[0] = default_arg;
		args[1] = NULL;
	}
	else
		ft_memcpy(args + write_idx, args + read_idx, (argc - write_idx) * sizeof(char *));
}
