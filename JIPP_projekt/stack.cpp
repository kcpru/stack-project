#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "error.h"

#pragma warning(disable: 4996)

void initStack(Stack* stack) {
    stack->top = NULL;
}

void freeStack(Stack* stack) {
    while (stack->top != NULL) {
        StackNode* temp = stack->top;
        stack->top = stack->top->next;
        free(temp->data);
        free(temp);
    }
}

void push(Stack* stack, void* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        handleErrorMessage("Nie mozna zaalokowac pamieci dla nowego elementu stosu");
        return;
    }
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

void* pop(Stack* stack) {
    if (stack->top == NULL) {
        handleErrorMessage("Stos jest pusty");
        return NULL;
    }
    StackNode* topNode = stack->top;
    void* data = topNode->data;
    stack->top = topNode->next;
    free(topNode);
    return data;
}

void* find(Stack* stack, int (*compare)(void*, void*), void* target) {
    StackNode* currentNode = stack->top;
    while (currentNode != NULL) {
        if (compare(currentNode->data, target) == 0) {
            return currentNode->data;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

void printStack(Stack* stack, void (*print)(void*)) {
    StackNode* currentNode = stack->top;
    while (currentNode != NULL) {
        print(currentNode->data);
        currentNode = currentNode->next;
    }
}

static bool isEmpty(Stack* stack) {
	return stack->top == NULL;
}

void saveStackToFile(Stack* stack, const char* filename, void (*saveData)(void* data, FILE* file)) {
    if (stack == NULL || filename == NULL || saveData == NULL) {
        handleErrorMessage("Invalid parameters in saveStackToFile");
        return;
    }

    FILE* file = fopen(filename, "wb");
    if (file == NULL) {
        handleErrorMessage("Error opening file in saveStackToFile");
        return;
    }

    StackNode* current = stack->top;
    while (current != NULL) {
        saveData(current->data, file);
        current = current->next;
    }

    fclose(file);
}

void loadStackFromFile(Stack* stack, const char* filename, void* (*loadData)(FILE* file)) {
    if (stack == NULL || filename == NULL || loadData == NULL) {
        handleErrorMessage("Invalid parameters in loadStackFromFile");
        return;
    }

    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        handleErrorMessage("Error opening file in loadStackFromFile");
        return;
    }

    Stack tempStack;
    initStack(&tempStack);

    while (1) {
        void* data = loadData(file);
        if (data == NULL) {
            break;
        }
        push(&tempStack, data);
    }

    fclose(file);

    while (!isEmpty(&tempStack)) {
        void* data = pop(&tempStack);
        push(stack, data);
    }

    freeStack(&tempStack);
}