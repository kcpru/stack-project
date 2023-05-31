#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "error.h"

#pragma warning(disable: 4996)

// Constants
#define MAX_FILENAME_LENGTH 100
#define MAX_STUDENT_NAME_LENGTH 100

// Colors
#define STYLE_INTERFACE "\033[47;30m"
#define STYLE_ERROR "\033[47;31m"
#define STYLE_ERROR_MESSAGE "\033[31m"
#define STYLE_SUCCESS "\033[42;30m"
#define STYLE_SUCCESS_MESSAGE "\033[32m"
#define STYLE_INFO "\033[43;30m"
#define STYLE_INFO_MESSAGE "\033[33m"
#define STYLE_RESET "\033[0m"

void printMenu() {
	printf(STYLE_INTERFACE "         Interface         \n" STYLE_RESET);
	printf(STYLE_INTERFACE "[a]" STYLE_RESET " Add student to stack\n");
	printf(STYLE_INTERFACE "[r]" STYLE_RESET " Remove student from stack\n");
	printf(STYLE_INTERFACE "[f]" STYLE_RESET " Find student on stack\n");
	printf(STYLE_INTERFACE "[p]" STYLE_RESET " Print stack elements\n");
	printf(STYLE_INTERFACE "[s]" STYLE_RESET " Save stack to file\n");
	printf(STYLE_INTERFACE "[l]" STYLE_RESET " Load stack from file\n");
	printf(STYLE_ERROR "[q]" STYLE_RESET STYLE_ERROR_MESSAGE " Quit\n" STYLE_RESET);
}

void stackInterface() {
	Stack stack;
	initStack(&stack);

	char choice;
	do {
		printMenu();
		printf("\nSelect an option:\n " STYLE_SUCCESS_MESSAGE "> " STYLE_RESET);
		scanf("%c", &choice);
		getchar();
		printf("\n");

		switch (choice) {
		case 'a': {
			char name[MAX_STUDENT_NAME_LENGTH];
			int birthYear;
			enum STUDY_FIELD studyField;

			printf("Enter student's last name: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0';

			printf("Enter birth year: ");
			scanf("%d", &birthYear);
			getchar();

			printf("Enter study field (0-INFORMATICS, 1-MATHEMATICS, 2-PHYSICS, 3-CHEMISTRY, 4-OTHER): ");
			int fieldChoice;
			scanf("%d", &fieldChoice);
			getchar();

			studyField = (enum STUDY_FIELD)fieldChoice;

			MY_STUDENT* student = createStudent(name, birthYear, studyField);
			if (student != NULL) {
				push(&stack, student);
				printf("Student added to the stack.\n");
			}
			break;
		}
		case 'r': {
			MY_STUDENT* student = (MY_STUDENT*)pop(&stack);
			if (student != NULL) {
				destroyStudent(student);
				printf(STYLE_SUCCESS_MESSAGE "Student removed from the stack.\n" STYLE_RESET);
			}
			break;
		}
		case 'f': {
			char name[MAX_STUDENT_NAME_LENGTH];
			printf("Enter student's last name to search for: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = '\0';

			MY_STUDENT targetStudent;
			targetStudent.name = name;

			MY_STUDENT* foundStudent = (MY_STUDENT*)find(&stack, compareStudentsByField, &targetStudent);
			if (foundStudent != NULL) {
				printf(STYLE_SUCCESS_MESSAGE "Student found on the stack:\n");
				printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Last Name: %s\n", foundStudent->name);
				printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Birth Year: %d\n", foundStudent->birthYear);
				printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Study Field: %d\n", foundStudent->studyField);
			}
			else {
				printf(STYLE_ERROR_MESSAGE "Student not found on the stack.\n" STYLE_RESET);
			}
			break;
		}
		case 'p': {
			printf(STYLE_SUCCESS_MESSAGE "Stack contents:\n" STYLE_RESET);
			printStack(&stack, (void (*)(void*))printStudent);
			break;
		}
		case 's': {
			char filename[MAX_FILENAME_LENGTH];
			printf("Enter the filename to save the stack: ");
			fgets(filename, sizeof(filename), stdin);
			filename[strcspn(filename, "\n")] = '\0';
			saveStackToFile(&stack, filename, saveStudent);
			break;
		}
		case 'l': {
			char filename[MAX_FILENAME_LENGTH];
			printf("Enter the filename to load the stack from: ");
			fgets(filename, sizeof(filename), stdin);
			filename[strcspn(filename, "\n")] = '\0';
			loadStackFromFile(&stack, filename, loadStudent);
			break;
		}
		case 'q':
			printf(STYLE_INFO "Program terminated.\n" STYLE_RESET);
			break;
		default:
			printf(STYLE_ERROR_MESSAGE "Invalid choice. Please try again.\n" STYLE_RESET);
			break;
		}

		printf("\n");
	} while (choice != 'q');

	freeStack(&stack);
}
