#ifndef ERROR_H
#define ERROR_H

typedef enum {
	ERROR_UNKNOWN,                // 0 - Nieznany błąd
	ERROR_MEMORY_ALLOCATION,      // 1 - Błąd przy alokacji pamięci
	ERROR_EMPTY_STACK,            // 2 - Stos jest pusty
	ERROR_INVALID_PARAMETERS,     // 3 - Nieprawidłowe parametry
	ERROR_FILE_OPEN,              // 4 - Błąd przy otwieraniu pliku
	ERRORS_COUNT                  // Liczba wszystkich kodów błędów
} ErrorCode;


void handle_error(errno_t error);
const char* error_message(errno_t error);

#endif /* ERROR_H */

