#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "error.h"

#pragma warning(disable: 4996)

MY_STUDENT* createStudent(const char* name, int birthYear, const char* studyField) {
	MY_STUDENT* student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (student == NULL) {
		handleErrorMessage("Nie mozna zaalokowac pamieci dla struktury MY_STUDENT");
		return NULL;
	}
	student->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (student->name == NULL) {
		handleErrorMessage("Nie mozna zaalokowac pamieci dla pola 'name' struktury MY_STUDENT");
		free(student);
		return NULL;
	}
	strcpy(student->name, name);
	student->birthYear = birthYear;
	student->studyField = (char*)malloc((strlen(studyField) + 1) * sizeof(char));
	if (student->studyField == NULL) {
		handleErrorMessage("Nie mozna zaalokowac pamieci dla pola 'studyField' struktury MY_STUDENT");
		free(student->name);
		free(student);
		return NULL;
	}
	strcpy(student->studyField, studyField);
	return student;
}

void destroyStudent(MY_STUDENT* student) {
	free(student->name);
	free(student->studyField);
	free(student);
}

int compareStudentsByField(void* student1, void* student2) {
	MY_STUDENT* s1 = (MY_STUDENT*)student1;
	MY_STUDENT* s2 = (MY_STUDENT*)student2;
	return strcmp(s1->name, s2->name);
}

void printStudent(void* student) {
	MY_STUDENT* s = (MY_STUDENT*)student;
	printf("\n| Nazwisko: %s\n", s->name);
	printf("| Rok urodzenia: %d\n", s->birthYear);
	printf("| Kierunek studiow: %s\n", s->studyField);
}

void saveStudent(void* data, FILE* file) {
	MY_STUDENT* student = (MY_STUDENT*)data;
	fprintf(file, "%s %d %s\n", student->name, student->birthYear, student->studyField);
}

void* loadStudent(FILE* file) {
	char name[100];
	int birthYear;
	char studyField[100];

	if (fscanf(file, "%s %d %s", name, &birthYear, studyField) != 3) {
		return NULL;
	}

	MY_STUDENT* student = createStudent(name, birthYear, studyField);
	return student;
}
