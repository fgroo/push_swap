#include "push_swap.h"

// Swaps two integer values. Helper for heapsort.
static void	swap_ints(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// The core logic of the heapsort algorithm.
static void	heapify(int *arr, int n, int i)
{
	int	largest;
	int	left;
	int	right;

	largest = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
	if (left < n && arr[left] > arr[largest])
		largest = left;
	if (right < n && arr[right] > arr[largest])
		largest = right;
	if (largest != i)
	{
		swap_ints(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

// Sorts an integer array using the Heapsort algorithm.
void	ft_heapsort(int *arr, int n)
{
	int	i;

	i = n / 2 - 1;
	while (i >= 0)
	{
		heapify(arr, n, i);
		i--;
	}
	i = n - 1;
	while (i > 0)
	{
		swap_ints(&arr[0], &arr[i]);
		heapify(arr, i, 0);
		i--;
	}
}

void	normalize_values(t_main *data)
{
	int	i;
	int	j;
	int	*sorted_copy;

	sorted_copy = (int *)malloc(data->count * sizeof(int));
	data->ranks = (int *)malloc(data->count * sizeof(int));
	if (!sorted_copy || !data->ranks)
	{
		ft_free((void **)&sorted_copy);
		handle_error(data);
	}
	i = -1;
	while (++i < data->count)
		sorted_copy[i] = data->values[i];
	ft_heapsort(sorted_copy, data->count);
	i = -1;
	while (++i < data->count)
	{
		j = -1;
		while (++j < data->count)
			if (data->values[i] == sorted_copy[j])
				data->ranks[i] = j;
	}
	ft_free((void **)&sorted_copy);
	ft_free((void **)&data->values);
}
