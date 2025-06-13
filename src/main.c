#include "push_swap.h"

// Going through the nodes and printing the values inside it.
void	print_stack(const char *label, t_stack *stack)
{
	t_stack	*current;

	ft_printf("%s ", label);
	if (stack == NULL)
	{
		ft_printf("(empty)\n");
		return ;
	}
	current = stack;
	ft_printf("%d ", current->value);
	current = current->next;
	while (current != stack)
	{
		ft_printf("%d ", current->value);
		current = current->next;
	}
	ft_printf("\n");
}

// Initializes the main data structure to default values.
static void	initialize_data(t_main *data)
{
	data->stack_a = NULL;
	data->stack_b = NULL;
	data->count = 0;
	data->values = NULL;
	data->ranks = NULL;
}

// The main entry point of the program.
// Orchestrates parsing, sorting, and cleanup.
int	main(int argc, char **argv)
{
	t_main	data;

	if (argc <= 1)
		return (0);
	initialize_data(&data);
	parse_arguments(argc, argv, &data);
	normalize_values(&data);
	initialize_stack_a(&data);
	if (!is_sorted(data.stack_a))
		sort_stacks(&data);
	//print_stack("\nstacka_AFTER\n\n", data.stack_a);
	free_stacks(&data);
	return (0);
}
