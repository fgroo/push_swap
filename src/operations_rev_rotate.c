#include "push_swap.h"

// rra: reverse rotate a - shift down all elements of stack a by 1.
void	do_rra(t_main *data)
{
	if (!data->stack_a || get_stack_size(data->stack_a) < 2)
		return ;
	data->stack_a = data->stack_a->prev;
	ft_printf("rra\n");
}

// rrb: reverse rotate b - shift down all elements of stack b by 1.
void	do_rrb(t_main *data)
{
	if (!data->stack_b || get_stack_size(data->stack_b) < 2)
		return ;
	data->stack_b = data->stack_b->prev;
	ft_printf("rrb\n");
}

// rrr: rra and rrb at the same time.
void	do_rrr(t_main *data)
{
	if (data->stack_a && get_stack_size(data->stack_a) > 1)
		data->stack_a = data->stack_a->prev;
	if (data->stack_b && get_stack_size(data->stack_b) > 1)
		data->stack_b = data->stack_b->prev;
	ft_printf("rrr\n");
}
