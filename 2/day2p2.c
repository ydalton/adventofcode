/*
 * ydalton (c) 2022
 *
 */
#include "day2.h"
#include <stdio.h>
#include <stdlib.h>


int getScore(enum Tool t, enum State s) {
    printf("tool: %d. state: %d. answer: %d\n", t, s, t + s*3);
    return t + s*3;
}

int main() {
    enum Tool tool;
    enum State state;

    /* error handling */
    FILE *fp = fopen("input.txt", "rb");
    if(!fp) {
        perror("Error: unable to open file!");
        return -1;
    }

    char c = fgetc(fp);
    unsigned int number = 0;
    unsigned int score = 0;

    /* as long as character is not the end of file character */
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
