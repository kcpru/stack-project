#ifndef DATA_H
#define DATA_H

#define MAX_FILENAME_LENGTH 128
#define MAX_STUDENT_NAME_LENGTH 128
#define STUDY_FIELD_COUNT 4

enum STUDY_FIELD {
    INFORMATICS,
    MATHEMATICS,
    PHYSICS,
    OTHER
};

extern const char* study_field_names[STUDY_FIELD_COUNT];

typedef struct {
    char* name;
    int name_length;
    int birth_year;
    enum STUDY_FIELD study_field;
} MY_STUDENT;

MY_STUDENT* create_student(const char* name, int birth_year, enum STUDY_FIELD study_field);
void destroy_student(MY_STUDENT* student);
int compare_students_by_field(void* student1, void* student2);
void print_student(void* student);
void save_student(void* data, FILE* file);
void* load_student(FILE* file);

#endif
