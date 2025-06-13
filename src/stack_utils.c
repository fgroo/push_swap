#include "push_swap.h"

// Returns the number of elements in a stack.
int	get_stack_size(t_stack *stack)
{
	int		size;
	t_stack	*current;

	if (!stack)
		return (0);
	size = 1;
	current = stack->next;
	while (current != stack)
	{
		size++;
		current = current->next;
	}
	return (size);
}

// Checks if the stack is perfectly sorted in ascending order.
int	is_sorted(t_stack *stack)
{
	t_stack	*current;

	if (!stack || stack->next == stack)
		return (1);
	current = stack;
	while (current->next != stack)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}

// Finds the 0-indexed position of a node with a specific value.
int	get_node_position(t_stack *stack, int value_to_find)
{
	int		position;
	t_stack	*current;

	if (!stack)
		return (-1);
	position = 0;
	current = stack;
	while (1)
	{
		if (current->value == value_to_find)
			return (position);
		position++;
		current = current->next;
		if (current == stack)
			break ;
	}
	return (-1);
}

// Finds the 0-indexed position of the node with the minimum value.
int	get_min_value_pos(t_stack *stack)
{
	t_stack	*current;
	int		min_val;
	int		min_pos;
	int		i;

	if (!stack)
		return (-1);
	current = stack;
	min_val = current->value;
	min_pos = 0;
	i = 0;
	while (1)
	{
		if (current->value < min_val)
		{
			min_val = current->value;
			min_pos = i;
		}
		current = current->next;
		i++;
		if (current == stack)
			break ;
	}
	return (min_pos);
}

// Finds the 0-indexed position of the node with the maximum value.
int	get_max_value_pos(t_stack *stack)
{
	t_stack	*current;
	int		max_val;
	int		max_pos;
	int		i;

	if (!stack)
		return (0);
	current = stack;
	max_val = current->value;
	max_pos = 0;
	i = 0;
	while (1)
	{
		if (current->value > max_val)
		{
			max_val = current->value;
			max_pos = i;
		}
		current = current->next;
		i++;
		if (current == stack)
			break ;
	}
	return (max_pos);
}
