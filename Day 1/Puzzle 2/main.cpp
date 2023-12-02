#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <cctype>

int main() {
    std::map<std::string, int> wordDigits = {{"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}, {"zero", 0}};
    std::vector<std::string> input;
    std::string line;
    std::ifstream fIn("input.txt");
    while (std::getline(fIn, line))
        input.push_back(line);
    fIn.close();

    int sum = 0;

    for (const auto& str : input) {
        std::string firstDigit, lastDigit;
        bool firstFound = false;

        for (size_t i = 0; i < str.size(); ++i) {
            if (std::isdigit(str[i])) {
                firstDigit = str[i];
                break;
            } else {
                for (const auto& pair : wordDigits) {
                    if (str.substr(i, pair.first.size()) == pair.first) {
                        firstDigit = std::to_string(pair.second);
                        firstFound = true;
                        break;
                    }
                }
            }
            if (firstFound) break;
        }

        for (size_t i = str.size(); i > 0; --i) {
            if (std::isdigit(str[i-1])) {
                lastDigit = str[i-1];
                break;
            } else {
                for (const auto& pair : wordDigits) {
                    if (i >= pair.first.size() && str.substr(i - pair.first.size(), pair.first.size()) == pair.first) {
                        lastDigit = std::to_string(pair.second);
                        break;
                    }
                }
            }
            if (!lastDigit.empty()) break;
        }

        sum += std::stoi(firstDigit + lastDigit);
    }

    std::cout << sum << "\n";

    return 0;
}
