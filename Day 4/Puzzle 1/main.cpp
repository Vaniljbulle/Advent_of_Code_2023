#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_set>
#include <sstream>

int main() {
    std::vector<std::string> input;
    std::string temp;
    std::ifstream fIn("input.txt");
    while (std::getline(fIn, temp)) {
        input.push_back(temp);
    }
    fIn.close();

    int sum = 0;

    for (auto& line : input) {
        std::unordered_set<int> winningNumbers;
        std::vector<int> numbers;
        std::istringstream iss(line);

        // Discard first 2 words
        iss >> temp >> temp;

        while (iss >> temp && temp != "|") winningNumbers.insert(std::stoi(temp));
        while (iss >> temp) numbers.push_back(std::stoi(temp));

        int score = 0;
        for (auto& number : numbers)
            if (winningNumbers.find(number) != winningNumbers.end())
                score == 0 ? score = 1 : score *= 2;
        sum += score;
    }

    std::cout << sum << std::endl;

    return 0;
}