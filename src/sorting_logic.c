#include "push_swap.h"

// High-level sorting dispatcher.
void	sort_stacks(t_main *data)
{
	if (data->count == 2)
		do_sa(data);
	else if (data->count == 3)
		sort_three(data);
	else
		turk_sort(data);
}

// Hard-coded logic to sort a stack of exactly three elements.
void	sort_three(t_main *data)
{
	int	top;
	int	mid;
	int	bot;

	if (is_sorted(data->stack_a))
		return ;
	top = data->stack_a->value;
	mid = data->stack_a->next->value;
	bot = data->stack_a->next->next->value;
	if (top > mid && mid < bot && top < bot)
		do_sa(data);
	else if (top > mid && mid > bot)
	{
		do_sa(data);
		do_rra(data);
	}
	else if (top > mid && mid < bot && top > bot)
		do_ra(data);
	else if (top < mid && mid > bot && top < bot)
	{
		do_sa(data);
		do_ra(data);
	}
	else if (top < mid && mid > bot && top > bot)
		do_rra(data);
}

// The main sorting algorithm for more than 3 elements.
// Pushes to B, then intelligently pushes back to A.
void	turk_sort(t_main *data)
{
	int	cost_a;
	int	cost_b;

	while (get_stack_size(data->stack_a) > 3)
		do_pb(data);
	sort_three(data);
	while (data->stack_b)
	{
		find_cheapest_move(data, &cost_a, &cost_b);
		execute_move(data, cost_a, cost_b);
		do_pa(data);
	}
	if (!is_sorted(data->stack_a))
		final_align_a(data);
}
