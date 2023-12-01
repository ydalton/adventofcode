/* this was actually quite short */
#include "../aoc.h"
#include <fstream>
#include <iostream>

#ifndef PART_TWO
# define NUM_OF_CHARS 4
#else
# define NUM_OF_CHARS 14
#endif

/* compare the letters of the string. return true
 * if all are different, false otherwise. */
bool cmp_string(std::string str) {
    for(unsigned int i = 0; i < str.length(); i++) {
        for(unsigned int j = 0; j < str.length(); j++) {
            if(i != j)
                if(str[i] == str[j])
                    return false;
        }
    }
    return true;
}

/* get 'num' chars from string 'str' starting from 'start'*/
std::string get_chars(std::string str,
                      unsigned int start, unsigned int num) {
    std::string new_str = "";
    for(unsigned int i = 0; i < num; i++)
        new_str.push_back(str[i + start]);
    return new_str;
}

unsigned int get_marker(std::string str) {
    unsigned int count = 0;
    std::string current_str = get_chars(str, count, NUM_OF_CHARS);
    while(!cmp_string(current_str)) {
        current_str = get_chars(str, count, NUM_OF_CHARS);
        if(cmp_string(current_str))
            return count + NUM_OF_CHARS;
        count++;
    }
    return 0;
}

int main() {
    std::ifstream file(INPUT_FILE);
    if(!file.is_open()) {
        std::cerr << "error: could not open file!\n";
        return -1;
    }

    std::string line;
    /* get a single line from file, then close it */
    getline(file, line);
    file.close();

    std::cout << get_marker(line);
}
