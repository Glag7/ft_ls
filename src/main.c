int	extract_opts(size_t argc, const char **argv, char *opts)
{
	static const char	accepted[] = "adfghlrRtU";

	for (size_t i = 1; i < argc; ++i)
	{
		const char	*cur = argv[i];

		if (cur[0] != '-')
			continue;
		if (cur[1] == '-' && cur[2] == '\0')
			break;
		for (size_t j = 1; j < ft_strlen(cur); ++j)
		{
			if (ft_at(cur[j], accepted) != -1)
				opts[cur[j]] = 1;
			else
			{
				//bad opt : cur[j]
				return 2;
			}
		}
	}
	return 0;
}
//si mauvaie opt ou malloc caca return 2

int	main(int argc, char **argv)
{
	char	**args;
	char	opts[255] = {0};
	int		err;

	err = extract_opts(argc, argv, &opts);
	if (err)
		return err;
	printf("caca\n");
	return 0;
}
