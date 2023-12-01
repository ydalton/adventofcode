#include "../aoc.h"
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>

int main() {
    std::string line;
    std::vector<int> totals;
    std::ifstream input(INPUT_FILE);
    if (!input.is_open()) {
        std::cerr << "Unable to open file!\n";
        return -1;
    }
    int tempValue = 0;
    while (std::getline(input, line)) {
        if (line == "") {
            totals.push_back(tempValue);
            tempValue = 0;
        } else {
            tempValue += stoi(line);
        }
    }
    input.close();
    /* Printing the values of the list */
    sort(totals.begin(), totals.end(), std::greater<int>());
    int threeLargest = totals[0] + totals[1] + totals[2];
    std::cout << totals[0] << '\n';
    std::cout << threeLargest << '\n';
    return 0;
}
