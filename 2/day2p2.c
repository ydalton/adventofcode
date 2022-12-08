/*
 * ydalton (c) 2022
 *
 * answer was 15702
 */
#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

int getScore(enum Tool t, enum State s) {
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
}

int main() {
    enum Tool tool;
    enum State state;

    FILE *fp = fopen("input.txt", "rb");
    /* error handling */
    if(!fp) {
        perror("Error: unable to open file!");
        return -1;
    }

    char c = fgetc(fp);
    unsigned int number = 0;
    unsigned int score = 0;

    /* my fucking dumbass did not realize 'tool' referred
     * to the enemy's draw, and not my draw. */
    while(c != EOF) {
        switch(c) {
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
        }
        if(number % 4 == 3)
            score += getScore(tool, state);
        number++;
        c = fgetc(fp);
    }
    fclose(fp);
    printf("%d\n", score);
    return 0;
}
