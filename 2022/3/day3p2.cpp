#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>

int compare_strings(std::vector<char> *cmp, std::string s1,
                    std::string s2, std::string s3) {
    std::vector<char> cl;       // common letters
    unsigned int i,j,k;
    i = j = k = 0;
    while(s1[i] != s2[j] != s3[k]) {
        k++;
        if(k >= s3.length() - 1) {
            j++;
            k = 0;
        } else if(!(j % s2.length())) {
            i++;
            j = 0;
        } else if(!(i % s1.length())) {
            return -1;
        }
        std::cout << k << '\n';
    }
    cl.push_back(s1[i]);
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

    std::ifstream file("test.txt");
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
