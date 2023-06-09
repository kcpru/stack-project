#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "error.h"

// Inicjalizuje stos, ustawiając wskaznik na szczyt na NULL.
void init_stack(Stack* stack) {
	stack->top = NULL;
}

// Zwalnia pamięć zajmowaną przez wszystkie elementy stosu.
// Jeżeli podano funkcję dealokującą danych, wywołuje ją dla każdego elementu przed ich usunięciem.
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

// Dodaje nowy element na szczyt stosu.
void push(Stack* stack, void* data) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		handle_error(1);
		return;
	}
	newNode->data = data;
	newNode->next = stack->top;
	stack->top = newNode;
}

// Usuwa i zwraca element ze szczytu stosu.
void* pop(Stack* stack) {
	if (stack->top == NULL) {
		handle_error(2);
		return NULL;
	}
	StackNode* topNode = stack->top;
	void* data = topNode->data;
	stack->top = topNode->next;
	free(topNode);
	return data;
}

// Wyszukuje elementy na stosie, które spełniają określone kryterium porównywania.
// Każdy pasujący element jest dodawany na osobny stos found_stack.
void search_in_stack(Stack* stack, int (*compare)(void*, void*), void* target, Stack* found_stack) {
	StackNode* current_node = stack->top;
	while (current_node != NULL) {
		if (compare(current_node->data, target) == 0) {
			push(found_stack, current_node->data);
		}
		current_node = current_node->next;
	}
}

// Wyświetla zawartość stosu, wywołując funkcję print dla każdego elementu.
void print_stack(Stack* stack, void (*print)(void*)) {
	StackNode* currentNode = stack->top;
	while (currentNode != NULL) {
		print(currentNode->data);
		currentNode = currentNode->next;
	}
}

// Sprawdza, czy stos jest pusty.
bool is_empty(Stack* stack) {
	return stack->top == NULL;
}

// Zapisuje zawartość stosu do pliku przy użyciu funkcji save_data.
bool save_stack_to_file(Stack* stack, const char* filename, void (*save_data)(void* data, FILE* file)) {
	if (stack == NULL || filename == NULL || save_data == NULL) {
		handle_error(3);
		return false;
	}

	FILE* file;
	if (fopen_s(&file, filename, "wb") != 0) {
		handle_error(4);
		return false;
	}

	StackNode* current = stack->top;
	while (current != NULL) {
		save_data(current->data, file);
		current = current->next;
	}

	fclose(file);

	return true;
}

// Wczytuje zawartość stosu z pliku przy użyciu funkcji load_data.
// Wczytane dane są uprzednio odkładane na tymczasowy stos, aby zachować kolejność zapisując je na główny stos.
// Dane z głównego stosu są usuwane przed wczytaniem nowych danych, aby uniknąć dublowania.
bool load_stack_from_file(Stack* stack, const char* filename, void* (*load_data)(FILE* file)) {
	if (stack == NULL || filename == NULL || load_data == NULL) {
		handle_error(3);
		return false;
	}

	FILE* file;
	if (fopen_s(&file, filename, "rb") != 0) {
		handle_error(4);
		return false;
	}

	Stack temp_stack;
	init_stack(&temp_stack);

	free_stack(stack, NULL);

	while (1) {
		void* data = load_data(file);
		if (data == NULL) {
			break;
		}
		push(&temp_stack, data);
	}

	while (!is_empty(&temp_stack)) {
		void* data = pop(&temp_stack);
		push(stack, data);
	}

	free_stack(&temp_stack, NULL);
	fclose(file);
	return true;
}
