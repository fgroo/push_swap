#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

/*
** --------------------------- Includes -----------------------------------------
*/

# include <stdlib.h> // For malloc, free, exit
# include <limits.h> // For INT_MAX, INT_MIN
# include <unistd.h> // For write
# include <libft.h> // For ft_printf

/*
** --------------------------- Structures ---------------------------------------
*/

// Node for the circular doubly-linked list representing a stack.
typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

// Master struct to hold all program data, passed to most functions.
typedef struct s_main
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	int		count;
	int		*values;
	int		*ranks;
}	t_main;

// A struct to hold the state during the single-pass scan of stack A.
typedef struct s_target_scan
{
	int	min_val;
	int	min_pos;
	int	best_fit_val;
	int	best_fit_pos;
}	t_target_scan;

// Struct for holding the integers that contain the costs for move operations.

typedef struct s_costs_lst
{
	int		cost_a;
	int		cost_b;
	int		*final_a;
	int		*final_b;
}	t_costs_lst;

/*
** --------------------------- Function Prototypes ------------------------------
*/

// --- error_handling.c ---
void	ft_free(void **ptr);
void	free_stacks(t_main *data);
void	handle_error(t_main *data);

// --- parsing.c ---
void	parse_arguments(int argc, char **argv, t_main *data);
long	ft_atol(const char *str);

// --- validation.c ---
void	validate_argument(const char *arg, t_main *data);
void	check_for_duplicates(t_main *data);

// --- preprocessing.c ---
void	normalize_values(t_main *data);
void	ft_heapsort(int *arr, int n);

// --- stack_init.c ---
void	initialize_stack_a(t_main *data);
t_stack	*create_new_node(int value);
void	add_node_to_stack_bottom(t_stack **stack, t_stack *new_node);

// --- stack_utils.c ---
int		get_stack_size(t_stack *stack);
int		is_sorted(t_stack *stack);
int		get_node_position(t_stack *stack, int value_to_find);
int		get_min_value_pos(t_stack *stack);
int		get_max_value_pos(t_stack *stack);

// --- operations_swap.c ---
void	do_sa(t_main *data);
void	do_sb(t_main *data);
void	do_ss(t_main *data);

// --- operations_push.c ---
void	do_pa(t_main *data);
void	do_pb(t_main *data);

// --- operations_rotate.c ---
void	do_ra(t_main *data);
void	do_rb(t_main *data);
void	do_rr(t_main *data);

// --- operations_rev_rotate.c ---
void	do_rra(t_main *data);
void	do_rrb(t_main *data);
void	do_rrr(t_main *data);

// --- sorting_logic.c ---
void	sort_stacks(t_main *data);
void	sort_three(t_main *data);
void	turk_sort(t_main *data);

// --- sorting_helpers.c ---
void	calculate_rotation_cost(t_stack *stack, int pos, int *moves);
void	find_cheapest_move(t_main *data, int *final_a, int *final_b);
void	execute_move(t_main *data, int cost_a, int cost_b);
void	final_align_a(t_main *data);

// --- sorting_helpers_utils.c ---
void	find_target_pos_in_a(t_main *data, int b_node_val, int *target_pos);

#endif