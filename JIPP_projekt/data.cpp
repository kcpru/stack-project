#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "error.h"
#include "interface.h"

#pragma warning(disable: 4996)

// Constants
#define MAX_STUDENT_NAME_LENGTH 100

// Colors
#define STYLE_INTERFACE "\033[47;30m"
#define STYLE_ERROR "\033[41;30m"
#define STYLE_ERROR_MESSAGE "\033[31m"
#define STYLE_SUCCESS "\033[42;30m"
#define STYLE_SUCCESS_MESSAGE "\033[32m"
#define STYLE_INFO "\033[43;30m"
#define STYLE_INFO_MESSAGE "\033[33m"
#define STYLE_RESET "\033[0m"

const char* studyFieldNames[] = {
	"INFORMATICS",
	"MATHEMATICS",
	"PHYSICS",
	"CHEMISTRY",
	"OTHER"
};

MY_STUDENT* createStudent(const char* name, int birthYear, enum STUDY_FIELD studyField) {
	MY_STUDENT* student = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (student == NULL) {
		handleErrorMessage("Failed to allocate memory for MY_STUDENT structure");
		return NULL;
	}
	student->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (student->name == NULL) {
		handleErrorMessage("Failed to allocate memory for 'name' field of MY_STUDENT structure");
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
	printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Last Name: %s\n", s->name);
	printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Birth Year: %d\n", s->birthYear);
	printf(STYLE_INFO_MESSAGE "| " STYLE_RESET "Study Field: %s\n\n", studyFieldNames[s->studyField]);
}

void saveStudent(void* data, FILE* file) {
	MY_STUDENT* student = (MY_STUDENT*)data;
	fprintf(file, "%s %d %s\n", student->name, student->birthYear, studyFieldNames[student->studyField]);
}

void* loadStudent(FILE* file) {
	char name[MAX_STUDENT_NAME_LENGTH];
	int birthYear;
	char studyFieldStr[128];

	if (fscanf(file, "%s %d %s", name, &birthYear, studyFieldStr) != 3) {
		return NULL;
	}

	enum STUDY_FIELD studyField;
	if (strcmp(studyFieldStr, "INFORMATICS") == 0) {
		studyField = INFORMATICS;
	}
	else if (strcmp(studyFieldStr, "MATHEMATICS") == 0) {
		studyField = MATHEMATICS;
	}
	else if (strcmp(studyFieldStr, "PHYSICS") == 0) {
		studyField = PHYSICS;
	}
	else if (strcmp(studyFieldStr, "CHEMISTRY") == 0) {
		studyField = CHEMISTRY;
	}
	else {
		studyField = OTHER;
	}

	MY_STUDENT* student = createStudent(name, birthYear, studyField);
	return student;

}
