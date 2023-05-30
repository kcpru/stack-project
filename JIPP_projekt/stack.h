#ifndef STACK_H
#define STACK_H

typedef struct {
	char* surname;
	int birthYear;
	char* studyField;
} MY_STUDENT;

// Inicjalizuje stos
void initStack();

// Zwolnienie stosu
void freeStack();

// Dodaje nowy element na stos
void push(MY_STUDENT* student);

// Pobiera pierwszy element ze stosu
MY_STUDENT* pop();

// Odnajduje podany element na stosie
MY_STUDENT* find(const char* surname);

// Zapisuje wszystkie elementy stosu do pliku binarnego
void saveStack(MY_STUDENT* student, const char* filename);

// Odczytuje elementy stosu z pliku binarnego
MY_STUDENT* loadStack(const char* filename);

// Wyprowadza elementy stosu na monitor
void printStack();

#endif  // STACK_H
