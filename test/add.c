#include "monty.h"

/**
* custom_addnode - add node to the head stack
* @head: head of the stack
* @n: new_value
*/
void custom_addnode(stack **head, int n)
{
	stack *new_node, *aux;

	aux = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (aux)
		aux->prev = new_node;
	new_node->n = n;
	new_node->next = *head;
	new_node->prev = NULL;
	*head = new_node;
}
