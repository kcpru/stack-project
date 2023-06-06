#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "interface.h"

//SF Pokazywale bardziej elegentny sposob.
void handle_error(int errorCode) {
	switch (errorCode) {
	case ERROR_MEMORY_ALLOCATION:
		printf("Error: Failed to allocate memory\n");
		break;
	case ERROR_EMPTY_STACK:
		printf("Error: The stack is empty\n");
		break;
	case ERROR_INVALID_PARAMETERS:
		printf("Error: Invalid parameters\n");
		break;
	case ERROR_FILE_OPEN:
		printf("Error: Failed to open the file\n");
		break;
	default:
		printf("Error: Unknown error\n");
		exit(errorCode); //SF przerywanie brutalne - brak wywolania globalnego dealokatora.

		break;
	}
}
