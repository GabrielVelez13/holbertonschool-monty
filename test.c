#include "monty.h"

Bus bus;

void custom_addnode(stack_t **head, int n) {
	stack_t *new_node, *aux;

	aux = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL) {
		perror("Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	if (aux)
		aux->prev = new_node;
	new_node->n = n;
	new_node->next = *head;
	new_node->prev = NULL;
	*head = new_node;
}

void custom_free_stack(stack_t *head) {
	stack_t *aux;

	aux = head;
	while (head) {
		aux = head->next;
		free(head);
		head = aux;
	}
}

int custom_execute(char *content, stack_t **stack, unsigned int counter, FILE *file) {
	stack_t *h;
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
		return 0;
	bus.arg = strtok(NULL, " \n\t");
	while (opst[i].opcode && op) {
		if (strcmp(op, opst[i].opcode) == 0) {
			opst[i].f(stack, counter);
			return 0;
		}
		i++;
	}
	if (op && opst[i].opcode == NULL) {
		fprintf(stderr, "L%d: unknown instruction %s\n", counter, op);
		fclose(file);
		free(content);
		custom_free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	return 1;
}

void custom_nop(stack_t **head) {
	(void) head;
}

void custom_pall(stack_t **head) {
	stack_t *h;

	h = *head;
	if (h == NULL)
		return;
	while (h) {
		printf("%d\n", h->n);
		h = h->next;
	}
}

void custom_pint(stack_t **head, unsigned int counter) {
	if (*head == NULL) {
		fprintf(stderr, "L%u: can't pint, stack empty\n", counter);
		fclose(bus.file);
		free(bus.content);
		custom_free_stack(*head);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*head)->n);
}

void custom_pop(stack_t **head, unsigned int counter) {
	stack_t *h;

	if (*head == NULL) {
		fprintf(stderr, "L%d: can't pop an empty stack\n", counter);
		fclose(bus.file);
		free(bus.content);
		custom_free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	*head = h->next;
	free(h);
}

void custom_push(stack_t **head, unsigned int counter) {
	int n, j = 0, flag = 0;

	if (bus.arg) {
		if (bus.arg[0] == '-')
			j++;
		for (; bus.arg[j] != '\0'; j++) {
			if (bus.arg[j] > ASCII_DIGIT_9 || bus.arg[j] < ASCII_DIGIT_0)
				flag = 1;
		}
		if (flag == 1) {
			fprintf(stderr, "L%d: usage: push integer\n", counter);
			fclose(bus.file);
			free(bus.content);
			custom_free_stack(*head);
			exit(EXIT_FAILURE);
		}
	} else {
		fprintf(stderr, "L%d: usage: push integer\n", counter);
		fclose(bus.file);
		free(bus.content);
		custom_free_stack(*head);
		exit(EXIT_FAILURE);
	}
	n = atoi(bus.arg);
	if (bus.lifi == 0)
		custom_addnode(head, n);
	else
		custom_addqueue(head, n);
}

void custom_queue(stack_t **head) {
	(void) head;
	bus.lifi = 1;
}

void custom_addqueue(stack_t **head, int n) {
	stack_t *new_node, *aux;
	
	aux = *head;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL) {
		perror("Error: malloc failed");
		exit(EXIT_FAILURE);
	}
	new_node->n = n;
	new_node->next = NULL;
	if (aux) {
		while (aux->next)
			aux = aux->next;
	}
	if (!aux) {
		*head = new_node;
		new_node->prev = NULL;
	} else {
		aux->next = new_node;
		new_node->prev = aux;
	}
	free(bus.content);
	fclose(bus.file);
}

void custom_swap(stack_t **head, unsigned int counter) {
	stack_t *h;
	int len = 0, aux;

	h = *head;
	while (h) {
		h = h->next;
		len++;
	}
	if (len < 2) {
		fprintf(stderr, "L%d: can't swap, stack too short\n", counter);
		fclose(bus.file);
		free(bus.content);
		custom_free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	aux = h->n;
	h->n = h->next->n;
	h->next->n = aux;
}

void custom_add(stack_t **head, unsigned int counter) {
	stack_t *h;
	int len = 0, sum;
	
	h = *head;
	while (h) {
		h = h->next;
		len++;
	}
	if (len < 2) {
		fprintf(stderr, "L%d: can't add, stack too short\n", counter);
		fclose(bus.file);
		free(bus.content);
		custom_free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	sum = h->n + h->next->n;
	h->next->n = sum;
	*head = h->next;
	free(h);
}

void custom_stack(stack_t **head, unsigned int counter) {
	(void) head;
	(void) counter;
	bus.lifi = 0;
}
