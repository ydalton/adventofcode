/*
 * ydalton (c) 2022
 */

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
#ifndef PART_TWO
    enum Tool tool1, tool2;
#else
    enum Tool tool;
    enum State state;
#endif

    /* error handling */
    FILE *fp = fopen(INPUT_FILE, "rb");
    if(!fp) {
        perror("Error: unable to open file");
        return -1;
    }

    char c = fgetc(fp);
    unsigned int score = 0;
    unsigned int number = 0;
#ifndef PART_TWO
    enum Tool* p_tool = &tool2;
#endif

    /* as long as character is not the end of file character */
    while(c != EOF) {
        switch(c) {
#ifndef PART_TWO
            case 'A':
            case 'B':
            case 'C':
                p_tool = &tool1;
                break;
            case 'X':
            case 'Y':
            case 'Z':
                p_tool = &tool2;
                break;
            default: break;
        }
        switch(c) {
            case 'A':
            case 'X':
                *p_tool = ROCK;
                break;
            case 'B':
            case 'Y':
                *p_tool = PAPER;
                break;
            case 'C':
            case 'Z':
                *p_tool = SCISSORS;
                break;
            default: break;
#else
            case 'A':
                tool = ROCK;
                break;
            case 'B':
                tool = PAPER;
                break;
            case 'C':
                tool = SCISSORS;
                break;
            case 'X':
                state = LOSE;
                break;
            case 'Y':
                state = DRAW;
                break;
            case 'Z':
                state = WIN;
                break;
            default: break;
#endif
        }
        if (number % 4 == 3)
            score += getScore(
            #ifndef PART_TWO
                tool1, tool2
            #else
                tool, state
            #endif
            );
        number++;
        c = fgetc(fp);
    }
    fclose(fp);
    printf("%d\n", score);
    return 0;
}

