#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

bool isValidArrangement(const std::string &row, const std::vector<int> &arrangement) {
    int index = 0;

    for(const auto& groupSize : arrangement) {
        int count = 0;

        while (index < row.length() && row[index] == '.') {
            index++;
        }

        while (index < row.length() && row[index] == '#') {
            count++;
            index++;
        }

        if (count != groupSize) {
            return false;
        }

        while (index < row.length() && row[index] == '.') {
            index++;
        }
    }

    while (index < row.length()) {
        if (row[index] == '#') {
            return false;
        }
        index++;
    }

    return true;
}


void solveRow(std::string &row, int index, const std::vector<int> &groupSizes, int &validCount) {
    if (index == row.length()) {
        if (isValidArrangement(row, groupSizes)) {
            validCount++;
        }
        return;
    }

    if (row[index] == '?') {
        row[index] = '.';
        solveRow(row, index + 1, groupSizes, validCount);

        row[index] = '#';
        solveRow(row, index + 1, groupSizes, validCount);

        // Backtrack
        row[index] = '?';
    } else {
        solveRow(row, index + 1, groupSizes, validCount);
    }
}

int main() {
    std::vector<std::string> input;
    std::vector<std::vector<int>> arrangements;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;
        std::istringstream iss(temp);
        std::string word;
        std::getline(iss, word, ' ');
        input.push_back(word);

        std::string numbers;
        std::getline(iss, numbers);
        std::istringstream iss2(numbers);
        std::string num;
        std::vector<int> arr;
        while (std::getline(iss2, num, ',')) {
            arr.push_back(std::stoi(num));
        }
        arrangements.push_back(arr);
    }
    fIn.close();

    int validCount = 0;

    for (int i = 0; i < input.size(); ++i) {
        solveRow(input[i], 0, arrangements[i], validCount);
    }

    std::cout << validCount << std::endl;


    return 0;
}
