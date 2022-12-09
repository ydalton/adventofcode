#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>

int compare_strings(std::vector<char> *cmp, std::string s1,
                    std::string s2, std::string s3) {
    std::vector<char> cl;       // common letters
    for(unsigned int i = 0; i < s1.length(); i++) {
        for(unsigned int j = 0; j < s2.length(); j++) {
            for(unsigned int k = 0; k < s3.length(); k++) {
                if(s1[i] == s2[j] == s3[k] &&
                   std::find(cl.begin(), cl.end(), s1[i]) == cl.end()) {
                    cl.push_back(s1[i]);
                }
            }
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
    std::string first, second, third;
    std::vector<char> chars;
    int total_priority = 0;

    std::ifstream file("input.txt");
    // error handling
    if(!file.is_open()) {
        std::cerr << "error: file could not be opened!\n";
        return -1;
    }
    while(getline(file, first)) {
        getline(file, second);
        getline(file, third);
        std::cout << first << '\n' << second << '\n' << third << '\n';
        // std::cout << first << ' ' << second << '\n';
        if(!compare_strings(&chars, first, second, third)) {
            for(unsigned int i = 0; i < chars.size(); i++) {
                total_priority += get_priority(chars[i]);
            }
        }
    }
    std::cout << '\n';
    std::cout << total_priority << '\n';
    return 0;
}
