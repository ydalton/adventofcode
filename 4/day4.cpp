/*
 *
 */
#include "../aoc.h"
#include <iostream>
#include <fstream>
#include <string>

#define NUM_OF_DIGITS 4

bool isdigit(char c) {
    if(c >= '0' && c <= '9')
        return true;
    else
        return false;
}

bool checkInside(int _pair[NUM_OF_DIGITS]) {
    return ((_pair[0] >= _pair[2])
            && (_pair[1] <= _pair[3]))
        || ((_pair[0] <= _pair[2])
            && (_pair[1] >= _pair[3]))
        ? true : false;
}

bool checkOverlap(int _pair[NUM_OF_DIGITS]) {
    return (((_pair[1] - _pair[2]) >= 0 )
            && ((_pair[3] - _pair[0]) >= 0))
        ? true : false;
}

int main() {
    int pair[NUM_OF_DIGITS];
    unsigned int assignment_pairs = 0;

    std::string buffer = "";
    std::string line;
    std::ifstream file(INPUT_FILE);
    if(!file.is_open()) {
        std::cerr << "error: failed to open file!" << '\n';
        return -1;
    }

    while(getline(file, line)) {
        // std::cout << line << '\n';
        unsigned pcount = 0;
        for(unsigned int i = 0; i < line.length() + 1; i++) {
            if(!isdigit(line[i])) {
                pair[pcount] = stoi(buffer);
                buffer = "";
                pcount++;
            } else {
                buffer.push_back(line[i]);
            }
        }

#ifndef PART_TWO
        if(checkInside(pair))
#else
        if(checkOverlap(pair))
#endif
            assignment_pairs++;
        // the logic behind it
        // zero out the buffer
        for(unsigned int i = 0; i < NUM_OF_DIGITS; i++) {
            pair[i] = 0;
        }
    }
    std::cout << assignment_pairs << '\n';
}
