#include "monty.h"

/**
* custom_free_stack - frees a doubly linked list
* @head: head of the stack
*/
void custom_free_stack(stack *head)
{
	stack *aux;

	aux = head;
	while (head)
	{
		aux = head->next;
		free(head);
		head = aux;
	}
}
