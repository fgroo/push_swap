#include "push_swap.h"

// Helper function to push the top node from one stack to another.
static void	push(t_stack **src, t_stack **dest)
{
	t_stack	*node_to_move;

	if (!src || !*src)
		return ;
	node_to_move = *src;
	if (node_to_move->next == node_to_move)
		*src = NULL;
	else
	{
		*src = node_to_move->next;
		node_to_move->prev->next = node_to_move->next;
		node_to_move->next->prev = node_to_move->prev;
	}
	if (!*dest)
	{
		(free(0), *dest = node_to_move, node_to_move->next = node_to_move);
		node_to_move->prev = node_to_move;
	}
	else
	{
		node_to_move->next = *dest;
		node_to_move->prev = (*dest)->prev;
		(*dest)->prev->next = node_to_move;
		(free(0), (*dest)->prev = node_to_move, *dest = node_to_move);
	}
}

// pa: push top of b to top of a.
void	do_pa(t_main *data)
{
	if (!data->stack_b)
		return ;
	push(&data->stack_b, &data->stack_a);
	ft_printf("pa\n");
}

// pb: push top of a to top of b.
void	do_pb(t_main *data)
{
	if (!data->stack_a)
		return ;
	push(&data->stack_a, &data->stack_b);
	ft_printf("pb\n");
}
