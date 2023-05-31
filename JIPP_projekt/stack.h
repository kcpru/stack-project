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

void initStack(Stack* stack);
void freeStack(Stack* stack);
void push(Stack* stack, void* data);
void* pop(Stack* stack);
void* find(Stack* stack, int (*compare)(void*, void*), void* target);
void printStack(Stack* stack, void (*print)(void*));
void saveStackToFile(Stack* stack, const char* filename, void (*saveData)(void* data, FILE* file));
void loadStackFromFile(Stack* stack, const char* filename, void* (*loadData)(FILE* file));

#endif
