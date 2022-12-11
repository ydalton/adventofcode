# Advent Of Code
This is my code for the Advent Of Code challenge.

## Building
There is no `Makefile`; compilation is done directly with gcc/g++.
### Macros
There are two macros that you need to know when building any of these
C/C++ source files: `TEST_ATTEMPT` and `PART_TWO`. You can define
these macros in gcc or g++ with the -D flag as follows:

    g++ day4.cpp -o day4 -DTEST_ATTEMPT
    g++ day4.cpp -o day4 -DPART_TWO

If `TEST_ATTEMPT` is defined, the program will read from the test input `test.txt`
rather than the real input `input.txt`. If `PART_TWO` is defined, the program will 
give the 

## Link to Advent of Code
[Advent of Code](https://adventofcode.com/)
