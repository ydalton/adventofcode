/*
 * ydalton (c) 2022
 */

#include "day2.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int number = 0;

int getScore(enum Tool t1, enum Tool t2) {
    int s1 = t1 + 1;      /* opponent's score */
    int s2 = t2 + 1;      /* my score */
    /* check whether two of the same tools were drawn, in other words a draw. */
    if(s1 == s2)
        return s2 + 3;
    /*
     * if the difference between the two is 1, then take
     * the larger of the two, if the difference between
     * the two is 2, then take the smaller of the two
     */
    if((abs(s1 - s2) == 1 && s1 < s2) ||
       (abs(s1 - s2) == 2 && s1 > s2))
        return s2 + 6;
    else
        return s2 + 0;
    return 0;
}

int main() {
    enum Tool tool1, tool2;

    /* error handling */
    FILE *fp = fopen("input.txt", "rb");
    if(!fp) {
        perror("Error: unable to open file!");
        return -1;
    }

    char c = fgetc(fp);
    unsigned int score = 0;
    enum Tool* p_tool = &tool2;

    /* as long as character is not the end of file character */
    while(c != EOF) {
        switch(c) {
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
        }
        if (number % 4 == 3) score += getScore(tool1, tool2);
        number++;
        c = fgetc(fp);
    }
    fclose(fp);
    printf("%d\n", score);
    return 0;
}

