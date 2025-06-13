#include "push_swap.h"

// Calculates if it's cheaper to rotate (positive) or reverse-rotate (negative).
void	calculate_rotation_cost(t_stack *stack, int pos, int *moves)
{
	int	size;

	*moves = 0;
	if (!stack || pos < 0)
		return ;
	size = get_stack_size(stack);
	if (size <= 1 || pos >= size || pos == 0)
		return ;
	if (pos <= size / 2)
		*moves = pos;
	else
		*moves = pos - size;
}

// Helper to calculate total cost and update the cheapest move found so far.
static void	update_costs(t_costs_lst *costs, int *ch)
{
	int	total_cost;
	int	abs_a;
	int	abs_b;

	abs_a = costs->cost_a;
	if (costs->cost_a < 0)
		abs_a = -costs->cost_a;
	abs_b = costs->cost_b;
	if (costs->cost_b < 0)
		abs_b = -costs->cost_b;
	if ((costs->cost_a >= 0 && costs->cost_b >= 0)
		|| (costs->cost_a < 0 && costs->cost_b < 0))
	{
		if (abs_a > abs_b)
			total_cost = abs_a;
		else
			total_cost = abs_b;
	}
	else
		total_cost = abs_a + abs_b;
	if (total_cost < *ch)
	{
		(free(0), *ch = total_cost, *costs->final_a = costs->cost_a);
		*costs->final_b = costs->cost_b;
	}
}

// Iterates through stack B to find the element that is cheapest to move to A.
void	find_cheapest_move(t_main *data, int *final_a, int *final_b)
{
	t_stack		*curr_b;
	t_costs_lst	costs;
	int			i;
	int			cheapest_cost;
	int			target_pos;

	costs = (t_costs_lst){0};
	costs.final_a = final_a;
	costs.final_b = final_b;
	curr_b = data->stack_b;
	i = 0;
	cheapest_cost = INT_MAX;
	while (i < get_stack_size(data->stack_b))
	{
		calculate_rotation_cost(data->stack_b, i, &costs.cost_b);
		find_target_pos_in_a(data, curr_b->value, &target_pos);
		calculate_rotation_cost(data->stack_a, target_pos, &costs.cost_a);
		update_costs(&costs, &cheapest_cost);
		curr_b = curr_b->next;
		i++;
	}
}

// Executes the rotational moves based on calculated costs.
void	execute_move(t_main *data, int cost_a, int cost_b)
{
	while (cost_a > 0 && cost_b > 0)
	{
		do_rr(data);
		cost_a--;
		cost_b--;
	}
	while (cost_a < 0 && cost_b < 0)
	{
		do_rrr(data);
		cost_a++;
		cost_b++;
	}
	while (cost_a > 0 && cost_a--)
		do_ra(data);
	while (cost_a < 0 && cost_a++)
		do_rra(data);
	while (cost_b > 0 && cost_b--)
		do_rb(data);
	while (cost_b < 0 && cost_b++)
		do_rrb(data);
}

// Rotates stack A until the smallest element (rank 0) is at the top.
void	final_align_a(t_main *data)
{
	int	pos_of_zero;
	int	moves_needed;

	pos_of_zero = get_node_position(data->stack_a, 0);
	if (pos_of_zero == -1)
		return ;
	calculate_rotation_cost(data->stack_a, pos_of_zero, &moves_needed);
	while (moves_needed > 0)
	{
		do_ra(data);
		moves_needed--;
	}
	while (moves_needed < 0)
	{
		do_rra(data);
		moves_needed++;
	}
}
