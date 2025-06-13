#include "push_swap.h"

// sa: swap the first 2 elements at the top of stack a.
void	do_sa(t_main *data)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;
	t_stack	*last;

if (!data->stack_a || data->stack_a->next == data->stack_a)
		return ;
	first = data->stack_a;
	second = first->next;
	if (second->next == first)
		data->stack_a = second;
	else
	{
		third = second->next;
		last = first->prev;
		first->next = third;
		third->prev = first;
		second->prev = last;
		last->next = second;
		first->prev = second;
		second->next = first;
		data->stack_a = second;
	}
	ft_printf("sa\n");
}

// sb: swap the first 2 elements at the top of stack b.
void	do_sb(t_main *data)
{
	t_stack	*first;
	t_stack	*second;
	t_stack	*third;
	t_stack	*last;

	if (!data->stack_a || data->stack_a->next == data->stack_b)
		return ;
	first = data->stack_b;
	second = first->next;
	if (second->next == first)
		data->stack_b = second;
	else
	{
		third = second->next;
		last = first->prev;
		first->next = third;
		third->prev = first;
		second->prev = last;
		last->next = second;
		first->prev = second;
		second->next = first;
		data->stack_b = second;
	}
	ft_printf("sa\n");
}

// ss: sa and sb at the same time.
void	do_ss(t_main *data)
{
	do_sa(data);
	do_sb(data);
}
