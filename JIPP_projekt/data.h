#ifndef DATA_H
#define DATA_H

typedef struct {
    char* name;
    int birthYear;
    char* studyField;
} MY_STUDENT;

MY_STUDENT* createStudent(const char* name, int birthYear, const char* studyField);
void destroyStudent(MY_STUDENT* student);
int compareStudentsByField(void* student1, void* student2);
void printStudent(void* student);
void saveStudent(void* data, FILE* file);
void* loadStudent(FILE* file);

#endif
