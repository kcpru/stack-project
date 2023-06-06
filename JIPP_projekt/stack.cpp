#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "error.h"

#pragma warning(disable:4996)

void init_stack(Stack* stack) {
	stack->top = NULL;
}

void free_stack(Stack* stack, dealloc_node_fn deallocData) {
	while (stack->top != NULL) {
		StackNode* temp = stack->top;
		stack->top = stack->top->next;
		if (deallocData != NULL) {
			deallocData(temp->data);
		}
		free(temp);
	}
}

void push(Stack* stack, void* data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		handle_error(ERROR_MEMORY_ALLOCATION);
		return;
	}
	newNode->data = data;
	newNode->next = stack->top;
	stack->top = newNode;
}

void* pop(Stack* stack) {
	if (stack->top == NULL) {
		handle_error(ERROR_EMPTY_STACK);
		return NULL;
	}
	StackNode* topNode = stack->top;
	void* data = topNode->data;
	stack->top = topNode->next;
	free(topNode);
	return data;
}

void search_in_stack(Stack* stack, int (*compare)(void*, void*), void* target, Stack* found_stack) {
	StackNode* currentNode = stack->top;
	while (currentNode != NULL) {
		if (compare(currentNode->data, target) == 0) {
			push(found_stack, currentNode->data);
		}
		currentNode = currentNode->next;
	}
}

void print_stack(Stack* stack, void (*print)(void*)) {
	StackNode* currentNode = stack->top;
	while (currentNode != NULL) {
		print(currentNode->data);
		currentNode = currentNode->next;
	}
}

bool is_empty(Stack* stack) {
	return stack->top == NULL;
}

bool save_stack_to_file(Stack* stack, const char* filename, void (*saveData)(void* data, FILE* file)) {
	if (stack == NULL || filename == NULL || saveData == NULL) {
		handle_error(ERROR_INVALID_PARAMETERS);
		return false;
	}

	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0) {
		handle_error(ERROR_FILE_OPEN);
		return false;
	}

	StackNode* current = stack->top;
	while (current != NULL) {
		saveData(current->data, file);
		current = current->next;
	}

	fclose(file);

	return true;
}

bool load_stack_from_file(Stack* stack, const char* filename, void* (*loadData)(FILE* file)) {
	if (stack == NULL || filename == NULL || loadData == NULL) {
		handle_error(ERROR_INVALID_PARAMETERS);
		return false;
	}

	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0) {
		handle_error(ERROR_FILE_OPEN);
		return false;
	}

	while (1) {
		void* data = loadData(file);
		if (data == NULL) {
			break;
		}
		push(stack, data);
	}

	fclose(file);
	return true;
}
