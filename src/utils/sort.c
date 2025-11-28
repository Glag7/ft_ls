#include <stddef.h>
#include <sys/types.h>

static inline void	ft_swap(void **a, void **b)
{
	void	*tmp = *a;

	*a = *b;
	*b = tmp;
}

void	ft_qsort_ptr(void *arr_void, size_t count, ssize_t (*cmpfunc)(const void*, const void*))
{
	void		**arr = arr_void;

	if (count <= 1)
		return;
	if (count == 2)
	{
		if (cmpfunc(arr[0], arr[1]) > 0)
			ft_swap(arr + 0, arr + 1);
		return;
	}

	const void	*pivot = arr[count / 2];
	size_t		pivot_idx = 0;

	ft_swap(arr + count / 2, arr + count - 1);
	for (size_t i = 0; i < count -1; ++i)
	{
		if (cmpfunc(arr[i], pivot) <= 0)
		{
			ft_swap(arr + i, arr + pivot_idx);
			++pivot_idx;
		}
	}
	ft_swap(arr + pivot_idx, arr + count - 1);
	ft_qsort_ptr(arr, pivot_idx, cmpfunc);
	ft_qsort_ptr(arr + pivot_idx, count - pivot_idx, cmpfunc);
}
