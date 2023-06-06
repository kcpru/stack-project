#ifndef ERROR_H
#define ERROR_H

typedef enum {
	ERROR_NONE = 0,
	ERROR_MEMORY_ALLOCATION,
	ERROR_EMPTY_STACK,
	ERROR_INVALID_PARAMETERS,
	ERROR_FILE_OPEN
} ERROR_CODE;

void handle_error(int errorCode);

#endif
