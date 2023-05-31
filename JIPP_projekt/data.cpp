#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "error.h"

#pragma warning(disable: 4996)

const char* studyFieldNames[] = {
	"INFORMATYKA",
	"MATEMATYKA",
	"FIZYKA",
	"CHEMIA",
	"INNE"
};

MY_STUDENT* createStudent(const char* name, int birthYear, enum STUDY_FIELD studyField) {
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
	student->studyField = studyField;
	return student;
}


void destroyStudent(MY_STUDENT* student) {
	free(student->name);
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
	printf("| Kierunek studiow: %s\n", studyFieldNames[s->studyField]);
}


void saveStudent(void* data, FILE* file) {
	MY_STUDENT* student = (MY_STUDENT*)data;
	fprintf(file, "%s %d %s\n", student->name, student->birthYear, studyFieldNames[student->studyField]);
}


void* loadStudent(FILE* file) {
	char name[100];
	int birthYear;
	char studyFieldStr[100];

	if (fscanf(file, "%s %d %s", name, &birthYear, studyFieldStr) != 3) {
		return NULL;
	}

	enum STUDY_FIELD studyField;
	if (strcmp(studyFieldStr, "INFORMATYKA") == 0) {
		studyField = INFORMATYKA;
	}
	else if (strcmp(studyFieldStr, "MATEMATYKA") == 0) {
		studyField = MATEMATYKA;
	}
	else if (strcmp(studyFieldStr, "FIZYKA") == 0) {
		studyField = FIZYKA;
	}
	else if (strcmp(studyFieldStr, "CHEMIA") == 0) {
		studyField = CHEMIA;
	}
	else {
		studyField = INNE;
	}

	MY_STUDENT* student = createStudent(name, birthYear, studyField);
	return student;
}
