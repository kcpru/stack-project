#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"
#include "data.h"
#include "stack.h"
#include "error.h"

#pragma warning(disable: 4996)

void printMenu() {
    printf("\033[47;30m  ====== MENU ======  \033[0m\n");
    printf("1. Dodaj element do stosu\n");
    printf("2. Usun element ze stosu\n");
    printf("3. Znajdz element na stosie\n");
    printf("4. Wyswietl zawartosc stosu\n");
    printf("5. Zapisz zawartosc stosu do pliku\n");
    printf("6. Wczytaj zawartosc stosu z pliku\n");
    printf("\033[31m0. Wyjscie\033[0m\n");
    printf("==================\n");
}

void stackInterface() {
    Stack stack;
    initStack(&stack);

    int choice;
    do {
        printMenu();
        printf("Wybierz opcje: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1: {
            char name[100];
            int birthYear;
            enum STUDY_FIELD studyField;

            printf("Podaj nazwisko studenta: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            printf("Podaj rok urodzenia: ");
            scanf("%d", &birthYear);
            getchar();

            printf("Podaj kierunek studiow (0-INFORMATYKA, 1-MATEMATYKA, 2-FIZYKA, 3-CHEMIA, 4-INNE): ");
            int fieldChoice;
            scanf("%d", &fieldChoice);
            getchar();

            studyField = (enum STUDY_FIELD)fieldChoice;

            MY_STUDENT* student = createStudent(name, birthYear, studyField);
            if (student != NULL) {
                push(&stack, student);
                printf("Dodano studenta na stos.\n");
            }
            break;
        }
        case 2: {
            MY_STUDENT* student = (MY_STUDENT*)pop(&stack);
            if (student != NULL) {
                destroyStudent(student);
                printf("Usunieto studenta ze stosu.\n");
            }
            break;
        }
        case 3: {
            char name[100];
            printf("Podaj nazwisko studenta do wyszukania: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';

            MY_STUDENT targetStudent;
            targetStudent.name = name;

            MY_STUDENT* foundStudent = (MY_STUDENT*)find(&stack, compareStudentsByField, &targetStudent);
            if (foundStudent != NULL) {
                printf("Znaleziono studenta na stosie:\n");
                printf("Nazwisko: %s\n", foundStudent->name);
                printf("Rok urodzenia: %d\n", foundStudent->birthYear);
                printf("Kierunek studiow: %d\n", foundStudent->studyField);
            }
            else {
                printf("Nie znaleziono studenta na stosie.\n");
            }
            break;
        }
        case 4: {
            printf("Zawartosc stosu:\n");
            printStack(&stack, (void (*)(void*))printStudent);
            break;
        }
        case 5: {
            char filename[100];
            printf("Podaj nazwe pliku do zapisu: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            saveStackToFile(&stack, filename, saveStudent);
            break;
        }
        case 6: {
            char filename[100];
            printf("Podaj nazwe pliku do wczytania: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';
            loadStackFromFile(&stack, filename, loadStudent);
            break;
        }
        case 0:
            printf("Program zakonczony.\n");
            break;
        default:
            printf("Nieprawidlowy wybor. Sprobuj ponownie.\n");
            break;
        }

        printf("\n");
    } while (choice != 0);

    freeStack(&stack);
}
