#include "push_swap.h"

// ra: rotate a - shift up all elements of stack a by 1.
void	do_ra(t_main *data)
{
	if (!data->stack_a || get_stack_size(data->stack_a) < 2)
		return ;
	data->stack_a = data->stack_a->next;
	ft_printf("ra\n");
}

// rb: rotate b - shift up all elements of stack b by 1.
void	do_rb(t_main *data)
{
	if (!data->stack_b || get_stack_size(data->stack_b) < 2)
		return ;
	data->stack_b = data->stack_b->next;
	ft_printf("rb\n");
}

// rr: ra and rb at the same time.
void	do_rr(t_main *data)
{
	if (data->stack_a && get_stack_size(data->stack_a) > 1)
		data->stack_a = data->stack_a->next;
	if (data->stack_b && get_stack_size(data->stack_b) > 1)
		data->stack_b = data->stack_b->next;
	ft_printf("rr\n");
}
