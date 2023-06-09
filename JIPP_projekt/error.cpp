#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "interface.h"

static const char* ErrorMessages[] = {
	"Unknown error",                // 0 - Nieznany błąd
	"Failed to allocate memory",    // 1 - Nie udało się zaalokować pamięci
	"The stack is empty",           // 2 - Stos jest pusty
	"Invalid parameters",           // 3 - Nieprawidłowe parametry
	"Failed to open the file"       // 4 - Nie udało się otworzyć pliku
};

// Obsługuje błąd i wyświetla odpowiedni komunikat
void handle_error(errno_t error) {
	const char* message = error_message(error);
	printf(STYLE_ERROR_MESSAGE "Error: %s" STYLE_RESET "\n", message);

	// Gdy wystąpi nieznany błąd, kończy działanie programu
	if (error == 0) {
		exit(error);
	}
}

// Zwraca komunikat na podstawie kodu błędu
const char* error_message(errno_t error) {
	if (error <= 0 || error >= ERRORS_COUNT) {
		return ErrorMessages[ERROR_UNKNOWN];
	}
	return ErrorMessages[(int)error];
}
