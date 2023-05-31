#include <stdio.h>
#include "error.h"

// Colors
#define STYLE_ERROR "\033[41;30m"
#define STYLE_ERROR_MESSAGE "\033[31m"
#define STYLE_RESET "\033[0m"

void handleErrorMessage(const char* message) {
	printf(STYLE_ERROR "Error: " STYLE_RESET " %s\n", message);
}
