#include "student.h"
#include "stack.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

#define MAX_NAME_LENGTH 64

// Funkcja pomocnicza do zwalniania pamieci dla pojedynczego studenta
void freeStudent(MY_STUDENT* student) {
	free(student->surname);
	free(student->studyField);
	free(student);
}