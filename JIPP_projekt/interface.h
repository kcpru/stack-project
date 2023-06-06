#ifndef INTERFACE_H
#define INTERFACE_H

#include "stack.h"

// Colors
#define STYLE_INTERFACE "\033[47;30m"
#define STYLE_ERROR "\033[47;31m"
#define STYLE_ERROR_MESSAGE "\033[31m"
#define STYLE_SUCCESS "\033[42;30m"
#define STYLE_SUCCESS_MESSAGE "\033[32m"
#define STYLE_INFO "\033[46;30m"
#define STYLE_INFO_MESSAGE "\033[36m"
#define STYLE_RESET "\033[0m"

void stack_interface();

#endif
