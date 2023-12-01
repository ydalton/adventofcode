#include <stdio.h>
#include <stdlib.h>
#ifdef PART_TWO
#include <stdint.h>
#endif
#include <string.h>

#include "../aoc.h"

/*
 * Similar to assembly language. addx adds a number to the total, and also
 * increments the cycle number, noop only increments the cycle number.
 */

#define BUF_SIZE 16

#ifdef PART_TWO
#define FB_WIDTH 40
#define FB_HEIGHT 6
#define SPRITE(num) ((1UL << ((num))) | (1UL << ((num) - 1)) | (1UL << ((num) - 2)))

static void print_out_line(uint64_t fb)
{
        int i;
        char c;
        for (i = FB_WIDTH - 1; i >= 0; i--) {
                c = (fb & (1UL << i)) ? '#' : '.';
                putchar(c);
        }
        putchar('\n');
}

#endif


int main(void)
{
        unsigned int cycles = 0;
        int x = 1, sum = 0, current_num;
        char *buf, *ret, *instr;
        FILE *fp;
#ifdef PART_TWO
        uint64_t fb[FB_HEIGHT] = {0};
        uint64_t sprite = 0;
        size_t line_num = 0;
        size_t beam_pos;
        int i;
#endif

        fp = fopen(INPUT_FILE, "r");
        if(!fp) {
                perror("fopen");
                return EXIT_FAILURE;
        }

        buf = malloc(BUF_SIZE * sizeof(char));
        instr = malloc(8 * sizeof(char));
        memset(buf, 0, BUF_SIZE);
        memset(instr, 0, 8);

        do {
                ret = fgets(buf, BUF_SIZE, fp);
                /* truncate the newline */
                sscanf(buf, "%s", instr);
                cycles++;
#ifdef PART_TWO
                beam_pos = cycles % 40;
                if (beam_pos == 0)
                        line_num++;
                sprite = (x > 0) ? SPRITE(FB_WIDTH - x) : 0;
                fb[line_num] |= (sprite & (1UL << (FB_WIDTH - beam_pos)));
#endif
                /* doing this twice is ugly but should work */
                if ((cycles + 20) % 40 == 0)
                        sum += cycles * x;

                if(!strcmp(instr, "addx")) {
                        sscanf(buf, "%*s %d", &current_num);
                        cycles++;
#ifdef PART_TWO
                        beam_pos = cycles % 40;
                        fb[line_num] |= (sprite & (1UL << (FB_WIDTH - beam_pos)));
                        if (beam_pos == 0)
                                line_num++;
#endif
                        if ((cycles + 20) % 40 == 0)
                                sum += cycles * x;
                } else {
                        current_num = 0;
                }

                x += current_num;
        } while(ret != NULL);

#ifdef PART_TWO
        for(i = 0; i < FB_HEIGHT; i++)
                print_out_line(fb[i]);
#else
        printf("%d\n", sum);
#endif

        free(buf);
        free(instr);

        fclose(fp);

        return EXIT_SUCCESS;
}
