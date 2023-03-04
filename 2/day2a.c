#include "../aoc.h"

#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

int getScore(
#ifndef PART_TWO
             enum Tool t1,
             enum Tool t2) {
    /* check whether two of the same tools were drawn, in other words a draw. */
    if(t1 == t2)
        return t2 + 3;
    /*
     * if the difference between the two is 1, then take
     * the larger of the two, if the difference between
     * the two is 2, then take the smaller of the two
     */
    if((abs(t1 - t2) == 1 && t1 < t2) ||
       (abs(t1 - t2) == 2 && t1 > t2))
        return t2 + 6;
    else
        return t2 + 0;
    return 0;
#else
             enum Tool t, enum State s) {
    enum Tool myDraw;
    switch(s) {
        case LOSE:
            if(t > 1)
                myDraw = t - 1;
            else
                myDraw = SCISSORS;
            break;
        case DRAW:
            myDraw = t;
            break;
        case WIN:
            if(t < 3)
                myDraw = t + 1;
            else
                myDraw = ROCK;
            break;
    }
    return myDraw + (s*3);
#endif
}

int main() {
    char *line = (char *) malloc(16);
    FILE *fp = fopen(INPUT_FILE, "r");
    if(!fp) {
        perror("Error: unable to open file");
        return -1;
    }

    unsigned int score = 0;

    char draw1, draw2;
    enum Tool myDraw;
#ifndef PART_TWO
    enum Tool theirDraw;
#else
    enum State state;
#endif
    while(fgets(line, 16, fp)) {
        sscanf(line, "%c %c", &draw1, &draw2);
        /* printf("%c %c\n", draw1, draw2); */
        switch(draw1) {
            case 'A':
                myDraw = ROCK;
                break;
            case 'B':
                myDraw = PAPER;
                break;
            case 'C':
                myDraw = SCISSORS;
                break;
            default:
                fprintf(stderr, "Error!\n");
                return -1;
        }
        switch(draw2) {
#ifndef PART_TWO
            case 'X':
                theirDraw = ROCK;
                break;
            case 'Y':
                theirDraw = PAPER;
                break;
            case 'Z':
                theirDraw = SCISSORS;
                break;
#else
            case 'X':
                state = LOSE;
                break;
            case 'Y':
                state = DRAW;
                break;
            case 'Z':
                state = WIN;
                break;
#endif
            default:
                fprintf(stderr, "Error!\n");
                return -1;
        }
        score += getScore(
#ifndef PART_TWO
            myDraw, theirDraw
#else
            myDraw, state
#endif
);
    }
    printf("%u\n", score);
    return 0;
}
