#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "interface.h"
#include "data.h"
#include "stack.h"
#include "error.h"

static void print_menu() {
	printf(STYLE_INTERFACE "         Interface         " STYLE_RESET "\n");
	printf(STYLE_INTERFACE "[a]" STYLE_RESET " Add student to stack\n");
	printf(STYLE_INTERFACE "[r]" STYLE_RESET " Remove student from stack\n");
	printf(STYLE_INTERFACE "[f]" STYLE_RESET " Find student on stack\n");
	printf(STYLE_INTERFACE "[p]" STYLE_RESET " Print stack elements\n");
	printf(STYLE_INTERFACE "[s]" STYLE_RESET " Save stack to file\n");
	printf(STYLE_INTERFACE "[l]" STYLE_RESET " Load stack from file\n");
	printf(STYLE_ERROR "[q]" STYLE_RESET STYLE_ERROR_MESSAGE " Quit" STYLE_RESET "\n");
}


static void print_error_message(const char* message) {
	printf("\n" STYLE_ERROR_MESSAGE "%s" STYLE_RESET "\n", message);
}

static void print_success_message(const char* message) {
	printf("\n" STYLE_SUCCESS_MESSAGE "%s" STYLE_RESET "\n", message);
}

static void print_info_message(const char* message) {
	printf("\n" STYLE_INFO_MESSAGE "%s" STYLE_RESET "\n", message);
}

static void print_input_field() {
	printf(STYLE_SUCCESS_MESSAGE " > " STYLE_RESET);
}

void stack_interface() {
	Stack stack;
	init_stack(&stack);

	char choice;
	do {
		print_menu();
		printf("\nSelect an option\n");
		print_input_field();
		scanf_s("%c", &choice);
		getchar();
		printf("\n");

		if (isalpha(choice)) {
			choice = tolower(choice);

			switch (choice) {
			case 'a': {
				char name[MAX_STUDENT_NAME_LENGTH];
				int birth_year;
				enum STUDY_FIELD study_field;

				printf("Enter student's last name\n");
				print_input_field();
				fgets(name, sizeof(name), stdin);
				name[strcspn(name, "\n")] = '\0';

				if (strlen(name) > MAX_STUDENT_NAME_LENGTH - 1) {
					print_error_message("Invalid input. Last name is too long.");
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					break;
				}

				printf("Enter birth year\n");
				print_input_field();
				if (scanf_s("%d", &birth_year) != 1) {
					print_error_message("Invalid input. Birth year must be a number.");
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					break;
				}
				getchar();

				printf("Enter study field\n");
				for (int i = 0; i < STUDY_FIELD_COUNT; i++) {
					printf(STYLE_INFO_MESSAGE "[%d]" STYLE_RESET " %s\n", i, study_field_names[i]);
				}

				print_input_field();
				int fieldChoice;
				if (scanf_s("%d", &fieldChoice) != 1) {
					print_error_message("Invalid input. Study field must be a number.");
					int c;
					while ((c = getchar()) != '\n' && c != EOF);
					break;
				}
				getchar();

				if (fieldChoice < 0 || fieldChoice >= STUDY_FIELD_COUNT) {
					print_error_message("Invalid input. Study field number is out of range.");
					break;
				}

				study_field = (enum STUDY_FIELD)fieldChoice;

				MY_STUDENT* student = create_student(name, birth_year, study_field);
				if (student != NULL) {
					push(&stack, student);
					print_success_message("Student added to the stack.");
				}

				break;
			}
			case 'r': {
				MY_STUDENT* student = (MY_STUDENT*)pop(&stack);
				if (student != NULL) {
					destroy_student(student);
					print_success_message("Student removed from the stack.");
				}
				break;
			}
			case 'f': {
				char name[MAX_STUDENT_NAME_LENGTH];
				printf("Enter student's last name to search for: ");
				fgets(name, sizeof(name), stdin);
				name[strcspn(name, "\n")] = '\0';

				MY_STUDENT target_student;
				target_student.name = name;

				Stack found_students;
				init_stack(&found_students);
				search_in_stack(&stack, compare_students_by_field, &target_student, &found_students);

				if (is_empty(&found_students)) {
					print_error_message("Student not found on the stack.");
				}
				else {
					print_success_message("Student found on the stack:");
					print_stack(&found_students, print_student);
				}
				break;
			}
			case 'p': {
				print_success_message("Stack contents:");
				print_stack(&stack, (void (*)(void*))print_student);
				break;
			}
			case 's': {
				char filename[MAX_FILENAME_LENGTH];
				printf("Enter the filename to save the stack: ");
				fgets(filename, sizeof(filename), stdin);
				filename[strcspn(filename, "\n")] = '\0';

				int result = save_stack_to_file(&stack, filename, save_student);
				if (result) {
					print_success_message("Stack successfully saved to file.");
				}
				else {
					print_error_message("Error saving stack to file.");
				}
				break;
			}
			case 'l': {
				char filename[MAX_FILENAME_LENGTH];
				printf("Enter the filename to load the stack from: ");
				fgets(filename, sizeof(filename), stdin);
				filename[strcspn(filename, "\n")] = '\0';

				int result = load_stack_from_file(&stack, filename, load_student);
				if (result) {
					print_success_message("Stack successfully loaded from file.");
				}
				else {
					print_error_message("Error loading stack from file.");
				}
				break;
			}

			case 'q':
				print_info_message("Program terminated.");
				break;
			default:
				print_error_message("Invalid choice. Please select one of the available options.");
				break;
			}
		}
		else {
			print_error_message("Invalid option. Please enter a letter.");
		}

		printf("\n");
	} while (choice != 'q');

	free_stack(&stack, (dealloc_node_fn)destroy_student);
}
