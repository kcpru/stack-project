#include "interface.h"
#include "student.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_NAME_LENGTH 64

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

// Funkcja interfejsu do wywolywania funkcji
void stackInterface() {
	char choice;
	char surname[MAX_NAME_LENGTH];
	MY_STUDENT* student = NULL;

	while (1) {
		printMenu();
		printf("Enter your choice: ");
		scanf(" %c", &choice);

		switch (choice) {
		case 'a':
			student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

			printf("Enter surname: ");
			scanf("%s", surname);
			student->surname = strdup(surname);

			printf("Enter birth year: ");
			scanf("%d", &(student->birthYear));

			printf("Enter study field: ");
			scanf("%s", surname);
			student->studyField = strdup(surname);

			push(student);
			printf("Student added to the stack.\n\n");
			break;

		case 'r':
			student = pop();
			if (student != NULL) {
				printf("Removed student:\n");
				printf("Surname: %s\n", student->surname);
				printf("Birth year: %d\n", student->birthYear);
				printf("Study field: %s\n\n", student->studyField);
				freeStudent(student);
			}
			break;

		case 'f':
			printf("Enter surname to find: ");
			scanf("%s", surname);
			student = find(surname);
			if (student != NULL) {
				printf("Found student:\n");
				printf("Surname: %s\n", student->surname);
				printf("Birth year: %d\n", student->birthYear);
				printf("Study field: %s\n\n", student->studyField);
			}
			else {
				printf("Student not found.\n\n");
			}
			break;

		case 's':
			printf("Enter filename to save stack: ");
			scanf("%s", surname);
			if (student != NULL) {
				saveStack(student, surname);
				printf("Stack saved to file.\n\n");
			}
			else {
				printf("No student to save.\n\n");
			}
			break;

		case 'l':
			printf("Enter filename to load stack: ");
			scanf("%s", surname);
			if (loadStack(surname)) {
				printf("Stack loaded from file.\n\n");
			}
			break;

		case 'p':
			printStack();
			break;

		case 'c':
			freeStack();
			printf("Stack cleared.\n\n");
			break;

		case 'e':
			printf("Exiting the program.\n");
			freeStack();
			return;

		default:
			printf("Invalid choice. Please try again.\n\n");
			break;
		}
	}
}

// Wyprowadza menu interfejsu na monitor
void printMenu() {
	printf("Stack Menu:\n");
	printf("[a] Add student to stack\n");
	printf("[r] Remove student from stack\n");
	printf("[f] Find student on stack\n");
	printf("[s] Save stack to file\n");
	printf("[l] Load stack from file\n");
	printf("[p] Print stack elements\n");
	printf("[c] Clear stack\n");
	printf(COLOR_RED "[e] Exit\n" COLOR_RESET);
}
