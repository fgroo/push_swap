#include "push_swap.h"

void do_sx(t_stack **x)
{
	t_stack	*f;
	t_stack	*s;
	t_stack	*t;
	t_stack	*l;

	if (!x || !*x || (*x)->next == *x)
		return ;
	f = *x;
	s = f->next;
	t = s->next;
	l = f->prev;
	f->next = t;
	t->prev = f;
	s->prev = l;
	l->next = s;
	f->prev = s;
	s->next = f;
	*x = s;
}

void do_ss(t_main *data)
{
    do_sa(data);
    do_sb(data);
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
