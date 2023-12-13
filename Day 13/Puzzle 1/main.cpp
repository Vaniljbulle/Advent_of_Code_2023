#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

bool isPattern(const std::vector<std::string> &pattern, int index) {
    for (int i = 0; i < pattern.size(); ++i) {
        if (i+index < pattern.size() && index - i - 1 >= 0 && pattern[i + index] != pattern[index - i - 1]) {
            return false;
        }
    }
    return true;
}

int findPatternStartIndex(std::vector<std::string> &pattern) {
    for (int i = 1; i < pattern.size(); ++i) {
        if(pattern[i] == pattern[i - 1]) {
            if (isPattern(pattern, i)) {
                return i;
            }
        }
    }
    return -1;
}

std::vector<std::string> rotateRight(std::vector<std::string>& original) {
    int rows = original.size();
    int cols = original[0].size();
    std::vector<std::string> rotated(cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j] = original[i][j] + rotated[j];
        }
    }

    return rotated;
}

int main() {
    std::vector<std::vector<std::string>> input(1);
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) {
            input.resize(input.size() + 1);
            continue;
        }
        input[input.size()-1].push_back(temp);
    }
    fIn.close();

    int total = 0;
    for (auto& pattern : input) {
        int result = findPatternStartIndex(pattern);

        if (result == -1) {
            pattern = rotateRight(pattern);
            total += findPatternStartIndex(pattern);
        } else {
            total += result * 100;
        }
    }

    std::cout << total << std::endl;

    return 0;
}
