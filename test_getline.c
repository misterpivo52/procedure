#include "getline.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen("test_input.txt", "w");
    if (fp == NULL) {
        printf("Cannot create test file\n");
        return 1;
    }
    fprintf(fp, "Hello, world!\n");
    fprintf(fp, "Second line\n");
    fclose(fp);

    fp = fopen("test_input.txt", "r");
    if (fp == NULL) {
        printf("Cannot open test file\n");
        return 1;
    }

    nread = getline(&line, &len, fp);
    assert(nread == 14);
    assert(strcmp(line, "Hello, world!\n") == 0);
    printf("Test 1 passed\n");

    nread = getline(&line, &len, fp);
    assert(nread == 12);
    assert(strcmp(line, "Second line\n") == 0);
    printf("Test 2 passed\n");

    nread = getline(&line, &len, fp);
    assert(nread == -1);
    printf("Test 3 passed\n");

    fclose(fp);
    free(line);

    printf("\nAll tests passed\n");
    return 0;
}