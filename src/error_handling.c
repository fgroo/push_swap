#include "push_swap.h"

// Safely frees a pointer and sets it to NULL.
void	ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

// Frees all nodes in a given stack.
static void	free_single_stack(t_stack **stack)
{
	t_stack	*current;
	t_stack	*temp;
	t_stack	*last;

	if (!stack || !*stack)
		return ;
	last = (*stack)->prev;
	last->next = NULL;
	current = *stack;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	*stack = NULL;
}

// Frees all nodes in both stacks.
void	free_stacks(t_main *data)
{
	free_single_stack(&data->stack_a);
	free_single_stack(&data->stack_b);
}

// Central error-handling function. Frees all memory and exits.
void	handle_error(t_main *data)
{
	if (data)
	{
		ft_free((void **)&data->values);
		ft_free((void **)&data->ranks);
		free_stacks(data);
	}
	write(2, "Error\n", 6);
	exit(1);
}
