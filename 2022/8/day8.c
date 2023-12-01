#include "../aoc.h"
#include <stdio.h>

/*
 * for now, I will hard code the sizes,
 * but I will make it more general later.
 */

#ifdef TEST_ATTEMPT
#define WIDTH 5
#define HEIGHT 5
#else
#define WIDTH 99
#define HEIGHT 99
#endif

#define NUM_OF_SIDES 4

#define CHAR_TO_INT(c) (c - '0')
#define MAX(a, b) ((a >= b) ? a : b)

#define CONDITION (current >= highest)

static unsigned int scenic(int(*p_trees)[HEIGHT][WIDTH],
                           int x, int y) {
    int highest = (*p_trees)[y][x];

    int current;
    int scenic_score = 1;
    for(int i = x+1; i < WIDTH; i++) {
        current = (*p_trees)[y][i];
        if(CONDITION || i == WIDTH - 1) {
            scenic_score *= i - x;
            break;
        }
    }
    for(int i = x-1; i >= 0; i--) {
        current = (*p_trees)[y][i];
        if(CONDITION || i == 0) {
            scenic_score *= x - i;
            break;
        }
    }
    for(int i = y+1; i < HEIGHT; i++) {
        current = (*p_trees)[i][x];
        if(CONDITION || i == HEIGHT - 1) {
            scenic_score *= i - y;
            break;
        }
    }
    for(int i = y-1; i >= 0; i--) {
        current = (*p_trees)[i][x];
        if(CONDITION || i == 0) {
            scenic_score *= y - i;
            break;
        }
    }
    return scenic_score;
}

static unsigned int visible(int (*p_trees)[HEIGHT][WIDTH],
                            int x, int y) {
    int highest = (*p_trees)[y][x];

    /* int matrix[2]; */
    int current;
    /* all trees at the edge are automatically visible. */
    if(x == 0 || y == 0 || x == WIDTH-1 || y == HEIGHT-1)
        return 1;
    /* it's repetitive as hell but still "functional" */
    /* left */
    for(int i = x+1; i < WIDTH; i++) {
        current = (*p_trees)[y][i];
        if(CONDITION)
            break;
        if(i == WIDTH - 1)
            return 1;
    }
    /* right */
    for(int i = x-1; i >= 0; i--) {
        current = (*p_trees)[y][i];
        if(CONDITION)
            break;
        if(i == 0)
            return 1;
    }
    /* down */
    for(int i = y+1; i < HEIGHT; i++) {
        current = (*p_trees)[i][x];
        if(CONDITION)
            break;
        if(i == HEIGHT - 1)
            return 1;
    }
    /* up */
    for(int i = y-1; i >= 0; i--) {
        current = (*p_trees)[i][x];
        if(CONDITION)
            break;
        if(i == 0)
            return 1;
    }
    return 0;
}

int main() {
    char c;
    FILE *fp = fopen(INPUT_FILE, "r");
    if(!fp) {
        perror("Unable to open file");
        return -1;
    }

    int trees[WIDTH][HEIGHT];

    unsigned int x = 0;
    unsigned int y = 0;
    /* get input */
    do {
        if(c != '\n' && c != '\0') {
            trees[y][x] = CHAR_TO_INT(c);
            x++;
        }
        else if(c == '\n') {
            y++;
            x = 0;
        }
        c = fgetc(fp);
    } while(c != EOF);

    int add_to_trees = 0;
#ifndef PART_TWO
    unsigned int visible_trees = 0;
#else
    int highest_score = 0;
#endif
#ifdef DEBUG
    printf("Original trees: \n");
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            printf("%d ", trees[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
    printf("Output: \n");
#endif
    /* printf("%u\n", scenic(&trees, 2, 3)); */
#ifndef PART_TWO
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            add_to_trees = visible(&trees, j, i);
# ifdef DEBUG
            printf("%d ", add_to_trees);
# endif
            visible_trees += add_to_trees;
        }
# ifdef DEBUG
        putchar('\n');
# endif
    }
#endif
#ifdef PART_TWO
    for(int i = 0; i < HEIGHT; i++) {
        for(int j = 0; j < WIDTH; j++) {
            add_to_trees = scenic(&trees, j, i);
            highest_score = MAX(highest_score, add_to_trees);
        }
    }
#endif
#ifndef PART_TWO
    printf("%u\n", visible_trees);
#else
    printf("%u\n", highest_score);
#endif
    return 0;
}
