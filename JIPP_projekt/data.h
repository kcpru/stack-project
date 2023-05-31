#ifndef DATA_H
#define DATA_H

enum STUDY_FIELD {
    INFORMATICS,
    MATHEMATICS,
    PHYSICS,
    CHEMISTRY,
    OTHER
};

extern const char* studyFieldNames[];

typedef struct {
    char* name;
    int birthYear;
    enum STUDY_FIELD studyField;
} MY_STUDENT;


MY_STUDENT* createStudent(const char* name, int birthYear, enum STUDY_FIELD studyField);
void destroyStudent(MY_STUDENT* student);
int compareStudentsByField(void* student1, void* student2);
void printStudent(void* student);
void saveStudent(void* data, FILE* file);
void* loadStudent(FILE* file);

#endif
