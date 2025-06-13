#include "push_swap.h"

// Allocates and initializes a new stack node.
t_stack	*create_new_node(int value)
{
	t_stack	*new_node;

	new_node = (t_stack *)malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = new_node;
	new_node->prev = new_node;
	return (new_node);
}

// Adds a new node to the end of a stack (circular list).
void	add_node_to_stack_bottom(t_stack **stack, t_stack *new_node)
{
	t_stack	*last;

	if (!stack || !new_node)
		return ;
	if (!*stack)
	{
		*stack = new_node;
		return ;
	}
	last = (*stack)->prev;
	last->next = new_node;
	new_node->prev = last;
	new_node->next = *stack;
	(*stack)->prev = new_node;
}

// Populates stack_a with the normalized ranks.
void	initialize_stack_a(t_main *data)
{
	int		i;
	t_stack	*new_node;

	i = 0;
	while (i < data->count)
	{
		new_node = create_new_node(data->ranks[i]);
		if (!new_node)
			handle_error(data);
		add_node_to_stack_bottom(&data->stack_a, new_node);
		i++;
	}
	ft_free((void **)&data->ranks);
}
