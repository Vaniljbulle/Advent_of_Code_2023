#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <cstring>

int extrapolate(std::vector<int> &history) {
    std::vector<int> numbers;
    numbers.reserve(history.size() - 1);

    bool allZero = true;
    for (int i = 0; i < history.size() - 1; ++i) {
        numbers.push_back(history[i + 1] - history[i]);
        if (numbers[i] != 0) allZero = false;
    }

    if (allZero) return 0;
    else return numbers[numbers.size() - 1] + extrapolate(numbers);
}

int main() {
    std::vector<std::vector<int>> history;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;

        char *token = std::strtok(&temp[0], " ");
        std::vector<int> numbers;
        while (token != nullptr) {
            numbers.push_back(std::stoi(token));
            token = std::strtok(nullptr, " ");
        }

        history.push_back(numbers);
    }
    fIn.close();

    int result = 0;

    for (auto &numbers: history) {
        result += numbers[numbers.size() - 1] + extrapolate(numbers);
    }

    std::cout << result << std::endl;

    return 0;
}
