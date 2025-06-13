#include "push_swap.h"

// Converts an ASCII string to a long, handling whitespace and signs.
// Includes overflow checks for the long data type.
long	ft_atol(const char *str)
{
	long	res;
	int		sign;
	int		digits;

	(free(0), res = 0, sign = 1, digits = 0);
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (sign == 1 && res > (LONG_MAX - (*str - '0')) / 10)
			return (LONG_MAX);
		if (sign == -1 && - res < (LONG_MIN + (*str - '0')) / 10)
			return (LONG_MIN);
		(free(0), res = res * 10 + (*str - '0'), digits++, str++);
	}
	if (digits == 0)
		return (LONG_MAX);
	return (res * sign);
}

// Parses command-line arguments into an integer array.
void	parse_arguments(int argc, char **argv, t_main *data)
{
	int		i;
	long	val;

	data->count = argc - 1;
	data->values = (int *)malloc(data->count * sizeof(int));
	if (!data->values)
		handle_error(data);
	i = 0;
	while (i < data->count)
	{
		validate_argument(argv[i + 1], data);
		val = ft_atol(argv[i + 1]);
		if (val > INT_MAX || val < INT_MIN)
			handle_error(data);
		data->values[i] = (int)val;
		i++;
	}
	check_for_duplicates(data);
}
