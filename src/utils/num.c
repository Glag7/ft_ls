#include <stddef.h>

void	ft_fillnum(char *s, size_t num, size_t numlen)
{
	for (size_t i = numlen; i > 0;)
	{
		s[--i] = num % 10 + '0';
		num /= 10;
	}
}

size_t	ft_numlen(size_t num)
{
	if (num < 10ULL)
		return 1;
	if (num < 100ULL)
		return 2;
	if (num < 1000ULL)
		return 3;
	if (num < 10000ULL)
		return 4;
	if (num < 100000ULL)
		return 5;
	if (num < 1000000ULL)
		return 6;
	if (num < 10000000ULL)
		return 7;
	if (num < 100000000ULL)
		return 8;
	if (num < 1000000000ULL)
		return 9;
	if (num < 10000000000ULL)
		return 10;
	if (num < 100000000000ULL)
		return 11;
	if (num < 1000000000000ULL)
		return 12;
	if (num < 10000000000000ULL)
		return 13;
	if (num < 100000000000000ULL)
		return 14;
	if (num < 1000000000000000ULL)
		return 15;
	if (num < 10000000000000000ULL)
		return 16;
	if (num < 100000000000000000ULL)
		return 17;
	if (num < 1000000000000000000ULL)
		return 18;
	if (num < 10000000000000000000ULL)
		return 19;
	return 20;
}

void	ft_fillnum_human(char *s, size_t num, size_t numlen)
{
	static const size_t	pow10[] = {
	0ULL,
	1ULL,
	10ULL,
	100ULL,
	1000ULL,
	10000ULL,
	100000ULL,
	1000000ULL,
	10000000ULL,
	100000000ULL,
	1000000000ULL,
	10000000000ULL,
	100000000000ULL,
	1000000000000ULL,
	10000000000000ULL,
	100000000000000ULL,
	1000000000000000ULL,
	10000000000000000ULL,
	100000000000000000ULL,
	1000000000000000000ULL,
	10000000000000000000ULL,
	};
	static const char	prefix[] = "????kkkMMMGGGTTTPPPEEEZZZ";
	size_t				reallen = ft_numlen(num);

	if (reallen <= 3)
		return ft_fillnum(s, num, numlen);
	switch (reallen % 3)
	{
		case 0:
			if (num % pow10[reallen - 3] >= 1)
				num += pow10[reallen - 2];
			ft_fillnum(s, num / pow10[reallen - 2], 3);
			break;
		case 1:
			s[0] = num / pow10[reallen] + '0';
			s[1] = '.';
			s[2] = (num / pow10[reallen - 1]) % 10 + '0' + (num % pow10[reallen - 2] >= 1);
			break;
		case 2:
			s[0] = num / pow10[reallen] + '0';
			s[1] = (num / pow10[reallen - 1]) % 10 + '0' + (num % pow10[reallen - 2] >= 1);
			break;
	}
	s[numlen - 1] = prefix[reallen];
}
