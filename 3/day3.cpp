#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>

int compare_strings(std::vector<char> *cmp,
                    std::string s1, std::string s2) {
    std::vector<char> cl;       // common letters
    // check whether the two strings are the same length, otherwise it won't work
    if(s1.length() != s2.length())
        return -1;
    for(unsigned int i = 0; i < s1.length(); i++) {
        for(unsigned int j = 0; j < s2.length(); j++) {
            if(s1[i] == s2[j] && std::find(cl.begin(),
                                           cl.end(), s1[i]) == cl.end())
                cl.push_back(s1[i]);
        }
    }
    *cmp = cl;
    return 0;
}

int get_priority(char c) {
    if(c >= 'a')
        return c - 'a' + 1;
    else if(c >= 'A')
        return c - 'A' + 27;
    else return 0;
}

int main() {
    std::string rucksack, first, second;
    std::vector<char> chars;
    int total_priority = 0;

    std::ifstream file("input.txt");
    // error handling
    if(!file.is_open()) {
        std::cerr << "error: file could not be opened!\n";
        return -1;
    }
    while(getline(file, rucksack)) {
        first = rucksack.substr(0, rucksack.length()/2);
        second = rucksack.substr(rucksack.length()/2);
        // std::cout << first << ' ' << second << '\n';
        if(!compare_strings(&chars, first, second)) {
            for(unsigned int i = 0; i < chars.size(); i++) {
                total_priority += get_priority(chars[i]);
            }
        }
    }
    std::cout << '\n';
    std::cout << total_priority << '\n';
    return 0;
}
