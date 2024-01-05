#ifndef MONTY_H
#define MONTY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASCII_DIGIT_9 57
#define ASCII_DIGIT_0 48

typedef struct stack_t {
    int n;
    struct stack_t *prev;
    struct stack_t *next;
} stack_t;

typedef struct {
    char *arg;
    FILE *file;
    char *content;
    int lifi;
} Bus;

extern Bus bus;

typedef struct instruction_s
{
    char *opcode;
    void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void custom_addnode(stack_t **head, int n);
void custom_free_stack(stack_t *head);
int custom_execute(char *content, stack_t **stacked, unsigned int counter, FILE *file);
void custom_nop(stack_t **head);
void custom_pall(stack_t **head);
void custom_pint(stack_t **head, unsigned int counter);
void custom_pop(stack_t **head, unsigned int counter);
void custom_push(stack_t **head, unsigned int counter);
void custom_queue(stack_t **head);
void custom_swap(stack_t **head, unsigned int counter);
void custom_addqueue(stack_t **head, int n);
void custom_stack(stack_t **head, unsigned int counter);
void custom_stack(stack_t **head, unsigned int counter);
void custom_add(stack_t **head, unsigned int counter);

#endif
    