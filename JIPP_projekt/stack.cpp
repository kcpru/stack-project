#include "stack.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_NAME_LENGTH 64

typedef struct StackNode {
	MY_STUDENT* student;
	struct StackNode* next;
} StackNode;

static StackNode* top = NULL;

// Inicjowanie stosu
void initStack() {
	top = NULL;
}

// Zwolnienie stosu
void freeStack() {
	StackNode* temp;
	while (top != NULL) {
		temp = top;
		top = top->next;
		free(temp->student->surname);
		free(temp->student->studyField);
		free(temp->student);
		free(temp);
	}
}

// Dodawanie nowego elementu
void push(MY_STUDENT* student) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		handleErrorMessage("Memory allocation failed");
		return;
	}

	newNode->student = student;
	newNode->next = top;
	top = newNode;
}

// Pobieranie pierwszego elementu
MY_STUDENT* pop() {
	if (top == NULL) {
		handleErrorMessage("Stack is empty");
		return NULL;
	}

	StackNode* temp = top;
	MY_STUDENT* student = temp->student;
	top = top->next;
	free(temp);

	return student;
}

// Odnalezienie podanego elementu na stosie
MY_STUDENT* find(const char* surname) {
	StackNode* current = top;
	while (current != NULL) {
		if (strcmp(current->student->surname, surname) == 0) {
			return current->student;
		}
		current = current->next;
	}

	return NULL;
}

// Zapis wszystkich elementow stosu na dysk w plik binarny
void saveStack(MY_STUDENT* student, const char* filename) {
	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		handleErrorMessage("Failed to open the file for writing");
		return;
	}

	fwrite(student, sizeof(MY_STUDENT), 1, file);
	fwrite(student->surname, sizeof(char), MAX_NAME_LENGTH, file);

	fclose(file);
}

// Odczyt elementow stosu z dysku
MY_STUDENT* loadStack(const char* filename) {
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		handleErrorMessage("Failed to open the file for reading");
		return NULL;
	}

	MY_STUDENT* student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (student == NULL) {
		handleErrorMessage("Memory allocation failed");
		fclose(file);
		return NULL;
	}

	fread(student, sizeof(MY_STUDENT), 1, file);

	student->surname = (char*)malloc(sizeof(char) * MAX_NAME_LENGTH);
	if (student->surname == NULL) {
		handleErrorMessage("Memory allocation failed");
		free(student);
		fclose(file);
		return NULL;
	}

	fread(student->surname, sizeof(char), MAX_NAME_LENGTH, file);

	fclose(file);
	return student;
}

// Wyprowadzenie elementow stosu na monitor
void printStack() {
	if (top == NULL) {
		printf("Stack is empty.\n");

		return;
	}

	printf("Stack elements:\n");
	StackNode* current = top;
	while (current != NULL) {
		printf("Surname: %s\n", current->student->surname);
		printf("Birth year: %d\n", current->student->birthYear);
		printf("Study field: %s\n\n", current->student->studyField);
		current = current->next;
	}
}