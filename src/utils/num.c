#include <stddef.h>

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
