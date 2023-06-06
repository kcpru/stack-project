#ifndef STACK_H
#define STACK_H

#include <stdio.h>

typedef struct StackNode {
	void* data;
	struct StackNode* next;
} StackNode;

typedef struct {
	StackNode* top;
} Stack;

typedef void(*dealloc_node_fn)(void*);

void init_stack(Stack* stack);
void free_stack(Stack* stack, dealloc_node_fn deallocData);
bool is_empty(Stack* stack);
void push(Stack* stack, void* data);
void* pop(Stack* stack);
void search_in_stack(Stack* stack, int (compare)(void*, void*), void* target, Stack* found_stack);
void print_stack(Stack* stack, void (*print)(void*));
bool save_stack_to_file(Stack* stack, const char* filename, void (*saveData)(void* data, FILE* file));
bool load_stack_from_file(Stack* stack, const char* filename, void* (*loadData)(FILE* file));

#endif
