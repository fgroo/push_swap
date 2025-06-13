#include "push_swap.h"

// Checks if an argument string contains only valid numeric characters.
void	validate_argument(const char *arg, t_main *data)
{
	int	i;
	int	has_digit;

	i = 0;
	has_digit = 0;
	if (!arg || arg[0] == '\0')
		handle_error(data);
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			handle_error(data);
		has_digit = 1;
		i++;
	}
	if (!has_digit)
		handle_error(data);
}

// Checks for duplicate numbers after sorting the initial values.
void	check_for_duplicates(t_main *data)
{
	int	*sorted_copy;
	int	i;

	sorted_copy = (int *)malloc(data->count * sizeof(int));
	if (!sorted_copy)
		handle_error(data);
	i = -1;
	while (++i < data->count)
		sorted_copy[i] = data->values[i];
	ft_heapsort(sorted_copy, data->count);
	i = 0;
	while (i < data->count - 1)
	{
		if (sorted_copy[i] == sorted_copy[i + 1])
		{
			ft_free((void **)&sorted_copy);
			handle_error(data);
		}
		i++;
	}
	ft_free((void **)&sorted_copy);
}
