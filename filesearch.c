// By the ways, I've sent you an email and now I've sent you a private message on Canvas. Please check them when you have the time.
#include <stdio.h>
#include <string.h>

// Defines
#define INITIALARGS 1
#define BUFFERSIZE 256
#define SHORT_CUTOFF 20
// I think I screwed up and caused a bug in my previous assignment. Oh well, don't look for z/Z.
#define TEXT_LOWERSTART 96
#define TEXT_LOWEREND 122
#define TEXT_UPPERSTART 64
#define TEXT_UPPEREND 92
#define TEXT_OFFSET (TEXT_LOWERSTART - TEXT_UPPERSTART)

// Prototypes
char *uppercase(char *string);
char *lowercase(char *string);
FILE *open(char *file, char *mode);

int main(int argc, char *args[]) {
    char *inFile, *shortFile, *longFile;
    FILE *inPtr, *shortPtr, *longPtr;
    char buffer[BUFFERSIZE];
    int counterL, counterS;

    if (argc != INITIALARGS+3) {
        printf("ERROR: INVALID NUMBER OF ARGUMENTS SPECIFIED\n");
        return -1;
    }

    inFile = args[INITIALARGS+0];
    shortFile = args[INITIALARGS+1];
    longFile = args[INITIALARGS+2];

    inPtr = open(inFile, "r");
    shortPtr = open(shortFile, "w");
    longPtr = open(longFile, "w");

    if (inPtr == NULL || shortPtr == NULL || longPtr == NULL)
        return -2;

    counterL = 0;
    counterS = 0;
    while (!feof(inPtr)) {
        int bufferLen;
        fgets(buffer, BUFFERSIZE, inPtr);
        bufferLen = strlen(buffer);

        if (bufferLen <= SHORT_CUTOFF) {
            fputs(uppercase(buffer), shortPtr);
            counterS++;
        } else {
            fputs(lowercase(buffer), longPtr);
            counterL++;
        }
    }

    printf("Wrote %d lines into %s.\nWrote %d lines into %s.\n", counterS, shortFile, counterL, longFile);

    fclose(inPtr);
    fclose(shortPtr);
    fclose(longPtr);
}

FILE *open(char *file, char *mode) {
    FILE *ptr = fopen(file, mode);
    if (ptr == NULL) {
        char errStr[BUFFERSIZE];
        sprintf(errStr, "ERROR; FAILED TO OPEN \"%s\" WITH MODE \"%s\"", file, mode);
        perror(errStr);
        return NULL;
    }
    return ptr;
}


char *uppercase(char *string) {
    int length = strlen(string);
    for (int i=0; i < length; i++) {
        if (string[i] >= TEXT_LOWERSTART && string[i] <= TEXT_LOWEREND)
            string[i] = string[i] - TEXT_OFFSET;
    }
    return string;
}
char *lowercase(char *string) {
    int length = strlen(string);
    for (int i=0; i < length; i++) {
        if (string[i] >= TEXT_UPPERSTART && string[i] <= TEXT_UPPEREND)
            string[i] = string[i] + TEXT_OFFSET;
    }
    return string;
}