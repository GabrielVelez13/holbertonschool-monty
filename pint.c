#include "monty.h"
/**
* f_pint - prints the top
* @head: stack head
* @counter: line_number
*/
void custom_pint(stack **head, unsigned int counter)
{
	if (*head == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", counter);
		fclose(bus.file);
		free(bus.content);
		custom_free_stack(*head);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*head)->n);
}
