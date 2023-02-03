#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef util
#define SUCCESS 0
#define WRONG_ARGUMENTS 1
#define INPUT_FILE_ERROR 2
#define OUTPUT_FILE_ERROR 3
#define MISCELLAENOUS 4
#define util

/**
*Safely allocate the given size The program exits on failure.
*/
void *safeMalloc(size_t size);

/**
*Safely free the given pointer. The program exists on failure.
*/
void safeFree(void *ptr);

/**
*Print the given error message then exit with the given code
*/
void error(char *message, int code);

#endif
