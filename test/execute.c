#include "monty.h"

/**
* custom_execute - executes the opcode
* @content: line content
* @stack: head linked list - stack
* @counter: line_counter
* @file: pointer to monty file
*/
int custom_execute(char *content, stack **stacked, unsigned int counter, FILE *file)
{
	stack *h;
	int len = 0, aux;
	instruction_t opst[] = {
		{"push", custom_push},
		{"pall", custom_pall},
		{"pint", custom_pint},
		{"pop", custom_pop},
		{"swap", custom_swap},
		{"add", custom_add},
		{"nop", custom_nop},
		{"queue", custom_queue},
		{"stack", custom_stack},
		{NULL, NULL}
	};
	unsigned int i = 0;
	char *op;

	op = strtok(content, " \n\t");
	if (op && op[0] == '#')
		return (0);
	bus.arg = strtok(NULL, " \n\t");
	while (opst[i].opcode && op)
	{
		if (strcmp(op, opst[i].opcode) == 0)
		{
			opst[i].f(stacked, counter);
			return (0);
		}
		i++;
	}
	if (op && opst[i].opcode == NULL)
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
		fclose(file);
		free(content);
		custom_free_stack(*stacked);
		exit(EXIT_FAILURE);
	}
	return (1);
}
