#include "push_swap.h"

// Initializes the scanner state before iterating through stack A.
static void	init_target_scan(t_target_scan *scan)
{
	scan->min_val = INT_MAX;
	scan->min_pos = -1;
	scan->best_fit_val = INT_MAX;
	scan->best_fit_pos = -1;
}

// Updates the scan state based on the current node in stack A.
static void	update_scan_state(t_target_scan *s, t_stack *n, int b_v, int i)
{
	if (n->value < s->min_val)
	{
		s->min_val = n->value;
		s->min_pos = i;
	}
	if (n->value > b_v && n->value < s->best_fit_val)
	{
		s->best_fit_val = n->value;
		s->best_fit_pos = i;
	}
}

// Determines the final target position after the single-pass scan is complete.
static int	get_final_target_pos(t_target_scan *scan)
{
	if (scan->best_fit_pos != -1)
		return (scan->best_fit_pos);
	return (scan->min_pos);
}

// Finds the best position in stack A to insert a value from stack B.
// This optimized version performs a single pass over stack A.
void	find_target_pos_in_a(t_main *data, int b_val, int *t_pos)
{
	t_stack			*current_a;
	int				i;
	t_target_scan	scan;
	int				size_a;

	if (!data->stack_a)
	{
		*t_pos = 0;
		return ;
	}
	init_target_scan(&scan);
	current_a = data->stack_a;
	size_a = get_stack_size(data->stack_a);
	i = 0;
	while (i < size_a)
	{
		update_scan_state(&scan, current_a, b_val, i);
		current_a = current_a->next;
		i++;
	}
	*t_pos = get_final_target_pos(&scan);
}
