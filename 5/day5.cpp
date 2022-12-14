/* i wrote a lot of functions */

#include "../aoc.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

struct Instruction {
    unsigned int amnt;          // amount
    unsigned int src;           // source
    unsigned int dest;          // destination
};

bool isdigit(char c) {
    return (c >= '0' && c <= '9')
        ? true : false;
}

/* get the preamble (first ) of the text document. */
std::vector<std::string> get_preamble(std::ifstream *p_f, std::string *p_line) {
    std::vector<std::string> prmb;

    /* while the line isn't a newline character, which
     * separates the preamble from the actual instructions,
     * get lines and put them into string vector 'prmb'. */
    while(*p_line != "\n") {
        getline(*p_f, *p_line);
        *p_line += '\n';
        prmb.push_back(*p_line);
    }

    /* remove the empty lines at the back. */
    for(int i = 0; i < 2; i++)
        prmb.pop_back();
    return prmb;
}

/* then, from the preamble, parse it into a program usable string vector. */
std::vector<std::string> parse_map(std::vector<std::string> *p_map) {
    std::vector<std::string> new_map;
    /* get the size of the array. */
    std::string last_line = (*p_map)[p_map->size()];
    unsigned int map_length = stoi(last_line.substr(last_line.length() - 4));

    std::string current_stack;
    for(unsigned int i = 0; i < map_length; i++) {
        current_stack = "";
        for(int j = p_map->size()-1; j > -1; j--) {
             /* if the current location is not out of bounds, and
              * if the current character is not an empty space,
              * then append the current letter to the stack.
              */
            if(1+i*4 < (*p_map)[j].length() && (*p_map)[j][1+i*4] != ' ')
                current_stack.push_back((*p_map)[j][1+i*4]);
        }
        new_map.push_back(current_stack);
    }
    return new_map;
}

/* take one character from member 'mbr' of *p_map and copy them to a buffer *p_buf. */
void copy_to_buf(std::vector<std::string> *p_map, unsigned int mbr, unsigned int amnt, std::string *p_buf) {
    std::string *p_line = &(*p_map)[mbr];
    /* copy the final to buffer. */
    *p_buf = p_line->substr(p_line->length() - amnt);
    /* remove amnt characters from the stack */
    for(unsigned int i = 0; i < amnt; i++)
        p_line->pop_back();
    return;
}

/* then, add characters from *p_buf to *p_line */
void paste_to_stack(std::vector<std::string> *p_map, unsigned int mbr, std::string *p_buf) {
    std::string *p_line = &(*p_map)[mbr];
    for(unsigned int i = 0; i < p_buf->length(); i++)
        p_line->push_back((*p_buf)[i]);
    *p_buf = "";
    return;
}

/* after the preamble, parse the instructions and put them into a struct. */
struct Instruction parse_instruction(std::string *p_line) {
    struct Instruction instr;
    std::string str = "";
    unsigned int number;
    unsigned int count = 0;
    for(unsigned int i = 0; i < p_line->length(); i++) {
        if(isdigit((*p_line)[i])) {
            str.push_back((*p_line)[i]);
        } else if ((*p_line)[i] == ' ') {
            if(str != "") {
                number = stoi(str);
                switch(count) {
                    case 0:
                        instr.amnt = number;
                        break;
                    case 1:
                        instr.src = number;
                        break;
                }
                count++;
                str = "";
            }
        }
    }
    instr.dest = stoi(str);
    return instr;
}

/* execute the instructions on *p_map based on the contents of the struct 'instr'. */
void exec_instruction(struct Instruction instr, std::vector<std::string> *p_map) {
    std::string buffer;
#ifndef PART_TWO
    for(unsigned int i = 0; i < instr.amnt; i++) {
        copy_to_buf(&(*p_map), instr.src - 1, 1, &buffer);
        paste_to_stack(&(*p_map), instr.dest - 1, &buffer);
    }
#else
    copy_to_buf(&(*p_map), instr.src - 1, instr.amnt, &buffer);
    paste_to_stack(&(*p_map), instr.dest - 1, &buffer);
#endif
    return;
}

int main() {
    std::ifstream file(INPUT_FILE);
    if(!file.is_open()) {
        std::cerr << "error: cannot open file!";
        return -1;
    }

    std::string line;
    std::vector<std::string> preamble = get_preamble(&file, &line);

    std::vector<std::string> new_map = parse_map(&preamble);
    /* printing members of new_map, for debugging,
     * slash indicates end of current string. */
    for(unsigned int i = 0; i < new_map.size(); i++) {
        for(unsigned int j = 0; j < new_map[i].length(); j++)
            std::cout << new_map[i][j];
        std::cout << "\n";
    }

    std::cout << "-----------\n";
    struct Instruction instr;
    while(getline(file, line)) {
        instr = parse_instruction(&line);
        exec_instruction(instr, &new_map);
    }
    for(unsigned int i = 0; i < new_map.size(); i++){
        std::cout << new_map[i].back();
    }
    std::cout << '\n';

    file.close();
    return 0;
}
