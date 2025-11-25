#include "parse_args.h"

/*struct :
recursive bool

list directories bool (overrides recursive)(not really since it does not trigger)

show owner
shwo every other data

sort, funcptr, strcmp, sort by time or do not sort
reverse sort bool

hidden files bool

human sizes bool
*/

#include "utils.h"

int	main(int argc, char **argv)
{
	char	**args = argv;
	char	opts[255] = {0};
	int		err;

	err = extract_opts(argc, argv, opts);
	if (err)
		return err;
	extract_args(argc, args);
	//fill some struct with opts
	//list, sort, format, print
	
	//XXX
	printf("opts\n");
	for (int i = 0; i < 255; ++i)
	{
		if (opts[i])
			printf("%c\n", i);
	}
	printf("args\n");
	for (int i = 0; args[i]; ++i)
	{
		printf("%s\n", args[i]);
	}
	return 0;
}
