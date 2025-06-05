#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// --- Struct for stack nodes ---
typedef struct s_stack
{
	int             value; // This will store the normalized rank
	struct s_stack *next;
	struct s_stack *prev;
} t_stack;

// --- Struct to hold move costs for an element in B ---
typedef struct s_move_cost {
	t_stack *node_in_b;
	int      target_val_in_b;
	int      moves_b;
	int      moves_a;
	int      total_ops;
} t_move_cost;


// --- Preprocessing Function Prototypes ---
void ft_heapsort(int *arr, int n);
void heapify(int *arr, int n, int i);
void swap_ints(int *a, int *b);
long ft_atol(const char *str);

// --- Stack Operation Function Prototypes ---
t_stack *create_new_node(int value);
void add_node_to_stack_bottom(t_stack **stack, t_stack *new_node);
void print_stack(const char *label, t_stack *stack); // For debugging
void free_stack(t_stack **stack);
int get_stack_size(t_stack *stack);
int get_node_position_by_value(t_stack *stack, int value_to_find);

// Operations (printf calls are the output)
void do_sa(t_stack **stack_a);
void do_sb(t_stack **stack_b);
void do_ss(t_stack **stack_a, t_stack **stack_b);
void do_pa(t_stack **stack_a, t_stack **stack_b);
void do_pb(t_stack **stack_a, t_stack **stack_b);
void do_ra(t_stack **stack_a);
void do_rb(t_stack **stack_b);
void do_rr(t_stack **stack_a, t_stack **stack_b);
void do_rra(t_stack **stack_a);
void do_rrb(t_stack **stack_b);
void do_rrr(t_stack **stack_a, t_stack **stack_b);

// Sorting logic & helpers
void sort_three_elements(t_stack **stack_a);
int get_target_pos_in_a(t_stack *stack_a, int value_to_insert); // Simplified signature
void calculate_rotation_cost_to_top_by_pos(t_stack *stack, int target_pos, int *moves_needed);
void execute_cheapest_moves(t_stack **stack_a, t_stack **stack_b, t_move_cost best_move);
void push_swap_sort_core(t_stack **stack_a, t_stack **stack_b, int num_count);


// --- Main Program ---
int main(int argc, char *argv[]) {
	// --- 1. Argument Parsing and Preprocessing ---
	if (argc <= 1) return 0;

	int num_count = argc - 1;
	int *original_values = (int *)malloc(num_count * sizeof(int));
	int *sorted_values = (int *)malloc(num_count * sizeof(int));
	int *final_ranks = (int *)malloc(num_count * sizeof(int));

	if (!original_values || !sorted_values || !final_ranks) {
		fprintf(stderr, "Error\n");
		free(original_values); free(sorted_values); free(final_ranks);
		return 1;
	}

	for (int i = 0; i < num_count; i++) {
		char *current_arg = argv[i + 1];
		long val = ft_atol(current_arg);
		int is_valid_format = 1;
		if(current_arg == NULL || strlen(current_arg) == 0) is_valid_format = 0;
		else {
			for(size_t k=0; k < strlen(current_arg); ++k) {
				if (!((current_arg[k] >= '0' && current_arg[k] <= '9') ||
					  (k == 0 && (current_arg[k] == '-' || current_arg[k] == '+')))) {
					is_valid_format = 0; break;
				}
			}
			if (strlen(current_arg) == 1 && (current_arg[0] == '-' || current_arg[0] == '+')) is_valid_format = 0;
		}

		if (!is_valid_format) {
			 fprintf(stderr, "Error\n");
			 free(original_values); free(sorted_values); free(final_ranks);
			 return 1;
		}
		if ((val == LONG_MAX && strcmp(current_arg, "9223372036854775807") != 0 && strcmp(current_arg, "+9223372036854775807") != 0 ) ||
			(val == LONG_MIN && strcmp(current_arg, "-9223372036854775808") != 0 ) ||
			 val > INT_MAX || val < INT_MIN) {
			fprintf(stderr, "Error\n");
			free(original_values); free(sorted_values); free(final_ranks);
			return 1;
		}
		original_values[i] = (int)val;
	}

	for (int i = 0; i < num_count; i++) sorted_values[i] = original_values[i];
	ft_heapsort(sorted_values, num_count);

	for (int i = 0; i < num_count - 1; i++) {
		if (sorted_values[i] == sorted_values[i+1]) {
			fprintf(stderr, "Error\n");
			free(original_values); free(sorted_values); free(final_ranks);
			return 1;
		}
	}

	for (int i = 0; i < num_count; i++) {
		int original_num = original_values[i];
		for (int j = 0; j < num_count; j++) {
			if (original_num == sorted_values[j]) {
				final_ranks[i] = j; break;
			}
		}
	}
	free(original_values); free(sorted_values);

	// --- 2. Initialize Stacks ---
	t_stack *stack_a = NULL;
	t_stack *stack_b = NULL;

	for (int i = 0; i < num_count; i++) {
		t_stack *new_node = create_new_node(final_ranks[i]);
		if (!new_node) {
			fprintf(stderr, "Error\n");
			free_stack(&stack_a); free(final_ranks); return 1;
		}
		add_node_to_stack_bottom(&stack_a, new_node);
	}
	free(final_ranks);

	// --- 3. Sort the Stacks ---
	if (num_count > 1) {
		int sorted = 1;
		if (stack_a) {
			t_stack *current = stack_a;
			for(int i = 0; i < num_count; ++i) { 
				if (current->value != i) {
					sorted = 0;
					break;
				}
				if (i < num_count - 1) current = current->next;
			}
		} else if (num_count > 0) { sorted = 0; }

		if (!sorted) {
			push_swap_sort_core(&stack_a, &stack_b, num_count);
		}
	}
	print_stack("Stack A:", stack_a);
	print_stack("Stack B:", stack_b);

	free_stack(&stack_a);
	free_stack(&stack_b);

	return 0;
}

// --- Preprocessing Helper Functions ---
long ft_atol(const char *str) {
	long res = 0;
	int sign = 1;
	int i = 0;
	int d = 0;
	
	if (!str || !*str) return LONG_MAX;
	
	while (str[i] && (str[i]==' '||str[i]=='\t'||str[i]=='\n'||str[i]=='\v'||str[i]=='\f'||str[i]=='\r')) i++;
	

	if (str[i] && (str[i]=='-'||str[i]=='+')) { 
		if(str[i++]=='-') sign=-1; 
	}
	

	if (!str[i]) return LONG_MAX;
	

	while (str[i] && (str[i]>='0'&&str[i]<='9')) {

		if (sign==1) { 
			if (res > (LONG_MAX-(str[i]-'0'))/10) return LONG_MAX; 
		} else { 
			if (-res < (LONG_MIN+(str[i]-'0'))/10) return LONG_MIN; 
			if (-res == (LONG_MIN+(str[i]-'0'))/10 && (str[i]-'0') > -(LONG_MIN%10)) return LONG_MIN; 
		}
		
		res = res*10 + (str[i++]-'0'); 
		d++;
	}
	

	if (d==0 || str[i]) return LONG_MAX;
	
	return res*sign;
}

void swap_ints(int *a, int *b) {
	int t=*a;
	*a=*b;
	*b=t;
}

void heapify(int *a, int n, int i) {
	int l=i, L=2*i+1, R=2*i+2;
	if(L<n&&a[L]>a[l])l=L;
	if(R<n&&a[R]>a[l])l=R;
	if(l!=i){swap_ints(&a[i],&a[l]);heapify(a,n,l);}
}

void ft_heapsort(int *a, int n) {
	for(int i=n/2-1;i>=0;i--)heapify(a,n,i);
	for(int i=n-1;i>0;i--){swap_ints(&a[0],&a[i]);heapify(a,i,0);}
}

// --- Stack Helper Functions ---
t_stack *create_new_node(int value) {
	t_stack *nn = (t_stack *)malloc(sizeof(t_stack));
	if(nn){ nn->value=value; nn->next=nn; nn->prev=nn; }
	return nn;
}

void add_node_to_stack_bottom(t_stack **s, t_stack *nn) {
	if(!s||!nn)return;
	if(!*s){*s=nn;}else{
		t_stack*l=(*s)->prev;
		l->next=nn;
		nn->prev=l;
		nn->next=*s;
		(*s)->prev=nn;
	}
}

void print_stack(const char *label, t_stack *stack) {
	printf("%s ", label);
	if (stack == NULL) {
		printf("(empty)\n");
		return;
	}
	t_stack *current = stack;
	do {
		printf("%d ", current->value);
		current = current->next;
	} while (current != stack);
	printf("\n");
}

void free_stack(t_stack **s) {
	if(!s||!*s)return;
	t_stack*c=*s,*h=*s,*t;
	do{t=c;c=c->next;free(t);}while(c!=h);
	*s=NULL;
}

int get_stack_size(t_stack *stack) {
	if (!stack) return 0;
	int size = 0;
	t_stack *current = stack;
	do { 
		size++; 
		current = current->next; 
	} while (current != stack);
	return size;
}

int get_node_position_by_value(t_stack *stack, int value_to_find) {
	if (!stack) return -1;
	int position = 0;
	t_stack *current = stack;
	do { 
		if (current->value == value_to_find) return position;
		position++; 
		current = current->next; 
	} while (current != stack);
	return -1; 
}


// --- Push_Swap Operations (printf calls are the output) ---
void do_sa(t_stack **a) {
	if (!a || !*a || (*a)->next == *a) return;
	t_stack *f = *a, *s = f->next, *t = s->next, *l = f->prev;
	f->next = t;
	t->prev = f;
	s->prev = l;
	l->next = s;
	f->prev = s;
	s->next = f;
	*a = s;
	printf("sa\n");
}

void do_sb(t_stack **b) {
	if (!b || !*b || (*b)->next == *b) return;
	t_stack *f = *b, *s = f->next, *t = s->next, *l = f->prev;
	f->next = t;
	t->prev = f;
	s->prev = l;
	l->next = s;
	f->prev = s;
	s->next = f;
	*b = s;
	printf("sb\n");
}

void do_ss(t_stack **a, t_stack **b)
{
	t_stack *f;
	t_stack *s;
	t_stack *t;
	t_stack	*l;

	int p_a = 0, p_b = 0;
	if (a && *a && (*a)->next != *a) {
		f = *a, s = f->next, t = s->next, l = f->prev;
		f->next = t;
		t->prev = f;
		s->prev = l;
		l->next = s;
		f->prev = s;
		s->next = f;
		*a = s;
		p_a = 1;
	}
	if (b && *b && (*b)->next != *b)
	{
		t_stack *f = *b, *s = f->next, *t = s->next, *l = f->prev;
		f->next = t;
		t->prev = f;
		s->prev = l;
		l->next = s;
		f->prev = s;
		s->next = f;
		*b = s;
		p_b = 1;
	}
	if (p_a || p_b)
		printf("ss\n");
}

void do_pb(t_stack **a, t_stack **b)
{
	t_stack *m;

	if (!a || !*a)
		return ;
	m = *a;
	if (m->next == m)
		*a = NULL;
	else
	{
		*a = m->next;
		m->prev->next = m->next;
		m->next->prev = m->prev;
	}
	if (!*b)
		(free(0),*b = m, m->next = m, m->prev = m);
	else
	{
		m->next = *b;
		m->prev = (*b)->prev;
		(*b)->prev->next = m;
		(*b)->prev = m;
		*b = m;
	}
	printf("pb\n");
}

void do_pa(t_stack **a, t_stack **b)
{
	t_stack *m;

	if (!b || !*b)
		return;
	m = *b;
	if (m->next == m)
		*b = NULL;
	else
	{
		*b = m->next;
		m->prev->next = m->next;
		m->next->prev = m->prev;
	}
	if (!*a)
		(free(0),*a = m, m->next = m, m->prev = m);
	else
	{
		m->next = *a;
		m->prev = (*a)->prev;
		(*a)->prev->next = m;
		(*a)->prev = m;
		*a = m;
	}
	printf("pa\n");
}

void do_ra(t_stack **a)
{
	if (!a || !*a || (*a)->next == *a)
		return ;
	*a = (*a)->next;
	printf("ra\n");
}

void do_rb(t_stack **b)
{
	if (!b || !*b || (*b)->next == *b)
		return ;
	*b = (*b)->next;
	printf("rb\n");
}

void do_rr(t_stack **a, t_stack **b)
{
	int p_a;
	int p_b;

	p_a = 0,
	p_b = 0;
	if (a && *a && (*a)->next != *a)
	{
		*a = (*a)->next;
		p_a = 1;
	}
	if (b && *b && (*b)->next != *b)
	{
		*b = (*b)->next;
		p_b = 1;
	}
	if (p_a || p_b) printf("rr\n");
}

void do_rra(t_stack **a)
{
	if (!a || !*a || (*a)->next == *a)
		return ;
	*a = (*a)->prev;
	printf("rra\n");
}

void do_rrb(t_stack **b)
{
	if (!b || !*b || (*b)->next == *b)
		return ;
	*b = (*b)->prev;
	printf("rrb\n");
}

void do_rrr(t_stack **a, t_stack **b)
{
	int p_a;
	int p_b;

	p_a = 0,
	p_b = 0;
	if (a && *a && (*a)->next != *a)
	{
		*a = (*a)->prev;
		p_a = 1;
	}
	if (b && *b && (*b)->next != *b)
	{
		*b = (*b)->prev;
		p_b = 1;
	}
	if (p_a || p_b)
		printf("rrr\n");
}


// --- Sorting Logic & Helpers ---
void sort_three_elements(t_stack **stack_a)
{
	t_stack	*top;
	t_stack	*mid;
	t_stack	*bot;
	int		t;
	int		m;
	int		b;

	if (!stack_a || !*stack_a || get_stack_size(*stack_a) != 3)
		return ;
	top = *stack_a;
	mid = top->next;
	bot = mid->next;
	t=top->value;
	m=mid->value;
	b=bot->value;
	if (t>m && m<b && t<b)
		do_sa(stack_a);
	else if (t>m && m>b)
		(free(0), do_sa(stack_a), do_rra(stack_a));
	else if (t>m && m<b && t>b)
		do_ra(stack_a);
	else if (t<m && m>b && t<b)
		(free(0), do_sa(stack_a), do_ra(stack_a));
	else if (t<m && m>b && t>b)
		do_rra(stack_a);
}

void calculate_rotation_cost_to_top_by_pos(t_stack *stack, int target_pos, int *moves_needed)
{
	int	size;

	*moves_needed = 0;
	if (!stack || target_pos < 0)
		return ;
	size = get_stack_size(stack);
	if (size <= 1 || target_pos >= size || target_pos == 0)
		return ;
	if (target_pos <= size / 2)
		*moves_needed = target_pos;
	else
		*moves_needed = target_pos - size;
}

int get_target_pos_in_a(t_stack *stack_a, int value_to_insert)
{
	if (!stack_a) return 0;

	t_stack *current = stack_a;
	int current_pos = 0;
	int size_a = get_stack_size(stack_a);

	int min_val_in_a = current->value;
	int max_val_in_a = current->value;
	t_stack *min_node_ptr = current; 
	int min_node_pos = 0;

	for (int i = 0; i < size_a; ++i) {
		if (current->value < min_val_in_a)
		{
			min_val_in_a = current->value;
			min_node_ptr = current;
			min_node_pos = i;
		}
		if (current->value > max_val_in_a)
		{
			max_val_in_a = current->value;
		}
		current = current->next;
	}
	
	if (value_to_insert < min_val_in_a || value_to_insert > max_val_in_a) {

		return min_node_pos; 
	}

	current = stack_a; // Reset scan
	current_pos = 0;
	for (int i = 0; i < size_a; ++i) {
		if (value_to_insert > current->prev->value && value_to_insert < current->value) {
			return current_pos;
		}
		current_pos++;
		current = current->next;
	}

	return min_node_pos;
}


void execute_cheapest_moves(t_stack **stack_a, t_stack **stack_b, t_move_cost best_move) {
	int moves_a = best_move.moves_a;
	int moves_b = best_move.moves_b;

	while (moves_a > 0 && moves_b > 0) { do_rr(stack_a, stack_b); moves_a--; moves_b--; }
	while (moves_a < 0 && moves_b < 0) { do_rrr(stack_a, stack_b); moves_a++; moves_b++; }
	while (moves_a > 0) { do_ra(stack_a); moves_a--; }
	while (moves_a < 0) { do_rra(stack_a); moves_a++; }
	while (moves_b > 0) { do_rb(stack_b); moves_b--; }
	while (moves_b < 0) { do_rrb(stack_b); moves_b++; }
	do_pa(stack_a, stack_b);
}


void push_swap_sort_core(t_stack **stack_a, t_stack **stack_b, int num_count) {
	if (num_count <= 1) return; 
	if (num_count == 2) { if ((*stack_a)->value > (*stack_a)->next->value) do_sa(stack_a); return; }
	if (num_count == 3) { sort_three_elements(stack_a); return; }
	// if (num_count == 5) {sort_five_elements}
	
	// Phase 1: Push all to B
	while(*stack_a != NULL) {
		do_pb(stack_a, stack_b);
	}


	while (*stack_b != NULL) {
		t_move_cost best_overall_move;
		best_overall_move.total_ops = INT_MAX; 
		best_overall_move.node_in_b = NULL;

		t_stack *current_b_node = *stack_b;
		int b_size = get_stack_size(*stack_b); 

		for (int i = 0; i < b_size; ++i) { 
			t_move_cost current_element_cost;

			current_element_cost.target_val_in_b = current_b_node->value;

			calculate_rotation_cost_to_top_by_pos(*stack_b, i, &current_element_cost.moves_b);
			
			int target_a_idx = get_target_pos_in_a(*stack_a, current_b_node->value);
			calculate_rotation_cost_to_top_by_pos(*stack_a, target_a_idx, &current_element_cost.moves_a);
			
			int ops_a = abs(current_element_cost.moves_a);
			int ops_b = abs(current_element_cost.moves_b);
			
			if ((current_element_cost.moves_a * current_element_cost.moves_b) > 0) { 
				current_element_cost.total_ops = (ops_a > ops_b ? ops_a : ops_b); 
			} else {
				current_element_cost.total_ops = ops_a + ops_b; 
			}

			if (current_element_cost.total_ops < best_overall_move.total_ops) {
				best_overall_move = current_element_cost;
				best_overall_move.node_in_b = current_b_node;
			}
			current_b_node = current_b_node->next; 
		}

		if (best_overall_move.node_in_b != NULL) { 

			int pos_of_best_node_in_b = get_node_position_by_value(*stack_b, best_overall_move.target_val_in_b);
			calculate_rotation_cost_to_top_by_pos(*stack_b, pos_of_best_node_in_b, &best_overall_move.moves_b);
			
			execute_cheapest_moves(stack_a, stack_b, best_overall_move);
		} else {
			if (*stack_b) do_pa(stack_a, stack_b);
			else break;
		}
	}

	if (*stack_a != NULL && get_stack_size(*stack_a) == num_count && (*stack_a)->value != 0) {
		int pos_of_zero = get_node_position_by_value(*stack_a, 0);
		int moves_to_align_a = 0;
		if (pos_of_zero != -1) { 
			calculate_rotation_cost_to_top_by_pos(*stack_a, pos_of_zero, &moves_to_align_a);
			while (moves_to_align_a > 0) { do_ra(stack_a); moves_to_align_a--; }
			while (moves_to_align_a < 0) { do_rra(stack_a); moves_to_align_a++; }
		}
	}
}
