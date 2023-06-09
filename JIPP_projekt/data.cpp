#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "error.h"
#include "interface.h"

const char* study_field_names[] = {
	"Informatics",
	"Matematics",
	"Physics",
	"Other"
};

// Tworzy i inicjalizuje strukturę MY_STUDENT na podstawie podanych danych.
MY_STUDENT* create_student(const char* name, int birth_year, enum STUDY_FIELD study_field) {
	MY_STUDENT* student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (student == NULL) {
		handle_error(1);
		return NULL;
	}
	student->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (student->name == NULL) {
		handle_error(1);
		free(student);
		return NULL;
	}
	int name_length = strlen(name) + 1;
	strcpy_s(student->name, name_length, name);
	student->name_length = name_length;
	student->birth_year = birth_year;
	student->study_field = study_field;
	return student;
}

// Zwalnia pamięć zajmowaną przez strukturę MY_STUDENT.
void destroy_student(MY_STUDENT* student) {
	free(student->name);
	free(student);
}

// Porównuje dwa obiekty typu MY_STUDENT na podstawie pola "name".
int compare_students_by_field(void* student1, void* student2) {
	MY_STUDENT* s1 = (MY_STUDENT*)student1;
	MY_STUDENT* s2 = (MY_STUDENT*)student2;
	return strcmp(s1->name, s2->name);
}

// Wyświetla informacje o studencie.
void print_student(void* student) {
	MY_STUDENT* s = (MY_STUDENT*)student;
	printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Last Name: %s\n", s->name);
	printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Birth Year: %d\n", s->birth_year);
	printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Study Field: %s\n\n", study_field_names[s->study_field]);
}

// Zapisuje dane studenta do pliku.
void save_student(void* data, FILE* file) {
	MY_STUDENT* student = (MY_STUDENT*)data;
	fwrite(student, sizeof(MY_STUDENT), 1, file);
	fwrite(student->name, sizeof(char), student->name_length, file);
}

// Wczytuje dane studenta z pliku.
void* load_student(FILE* file) {
	MY_STUDENT temp_student;
	if (fread(&temp_student, sizeof(MY_STUDENT), 1, file) != 1) {
		return NULL;
	}

	char* name = (char*)malloc(sizeof(char) * temp_student.name_length);
	if (name == NULL) {
		handle_error(1);
		return NULL;
	}

	if (fread(name, sizeof(char), temp_student.name_length, file) != temp_student.name_length) {
		free(name);
		return NULL;
	}

	MY_STUDENT* student = create_student(name, temp_student.birth_year, temp_student.study_field);
	free(name);

	return student;
}
