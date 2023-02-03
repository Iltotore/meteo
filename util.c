#include <stdlib.h>
#include <stdio.h>
#include "util.h"

/**
*Safely allocate the given size. The program exits on failure.
*/
void *safeMalloc(size_t size) {
    void *pointer = malloc(size);
    if(pointer == NULL) {
        error("Memory allocation error", 4);
    }
    return pointer;
}

/**
*Safely free the given pointer. The program exists on failure.
*/
void safeFree(void *ptr) {
    if(ptr == NULL) {
        error("Tried to free NULL", 4);
    }
    free(ptr);
}

/**
*Exits the program with the right exit code
*/
void error(char *message, int code) {
    printf("\e[0;31mError: %s\e[0;0m\n", message);
    exit(code);
}