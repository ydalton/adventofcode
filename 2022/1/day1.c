/* as a challenge */

#include "../aoc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* not needed anymore */
#define LARGEST(a, b) ((a > b) ? a : b)

int cmpfunc(const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

int main() {
    char *buf = (char *) malloc(16);
    int current_num;
    unsigned int size_list = 1;
    int *values = (int *) malloc(256 * sizeof(int));
    FILE *input = fopen(INPUT_FILE, "r");
    if(input == NULL) {
        fprintf(stderr, "Unable to open file!\n");
        return -1;
    }
    /* read lines */
    while(fgets(buf, 16, input) != NULL) {
        if(strncmp(buf, "\n", 1) != 0)
            current_num += atoi(buf);
        else {
            size_list++;
            if(size_list >= 256) {
                values = (int *) malloc(512 * sizeof(int));
            }
            values[size_list] = current_num;
            current_num = 0;
        }
    }
    fclose(input);
    free(buf);
    int largest = 0;
#ifndef PART_TWO
    for(unsigned int i = 0; i < size_list; i++)
        largest = LARGEST(largest, values[i]);
    printf("%d\n", largest);
#else
    /* sort the array */
    qsort(values, size_list, sizeof(int), cmpfunc);
    for(unsigned int i = 0; i < 3; i++) {
        largest += values[size_list-i-1];
    }
    printf("%d\n", largest);
#endif
    free(values);
    return 0;
}
