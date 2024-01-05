#include "monty.h"
/**
 * f_pall - prints the stack
 * @head: stack head
 * @counter: no used
*/
void f_pall(stack **head, unsigned int counter)
{
	stack *h;
	(void)counter;

	h = *head;
	if (h == NULL)
		return;
	while (h)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
}
