#include <stdlib.h>
#include <stdio.h>
#include "util.h"
#include "string.h"

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
        error("Tried to free NULL",4);
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

/**
*Return the textual length of the given integer.
*/
int lengthOfInt(int n) {
    int i = 0;
    if(n < 0) i++;
    while(n != 0) {
        i++;
        n /= 10;
    }
    return i;
}

/**
*Clear/Flush the given stream.
*/
void clear(FILE *stream) {
    int nh;
    do {
        nh = fgetc(stream);
    } while(nh != EOF && nh != '\n');
}