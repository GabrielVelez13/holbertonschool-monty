#ifndef MONTY_H
#define MONTY_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack;
/**
 * struct bus_s - variables -args, file, line content
 * @arg: value
 * @file: pointer to monty file
 * @content: line content
 * @lifi: flag change stack <-> queue
 */
typedef struct bus_s
{
	char *arg;
	FILE *file;
	char *content;
	int lifi;
}  bus_t;
extern bus_t bus;
/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack **stack, unsigned int line_number);
} instruction_t;

void f_push(stack **head, unsigned int number);
void f_pall(stack **head, unsigned int number);
void f_pint(stack **head, unsigned int number);
int execute(char *content, stack **head, unsigned int counter, FILE *file);
void free_stack(stack *head);
void f_pop(stack **head, unsigned int counter);
void f_swap(stack **head, unsigned int counter);
void f_add(stack **head, unsigned int counter);
void f_nop(stack **head, unsigned int counter);
void addnode(stack **head, int n);
void addqueue(stack **head, int n);
void f_queue(stack **head, unsigned int counter);
void f_stack(stack **head, unsigned int counter);
#endif
