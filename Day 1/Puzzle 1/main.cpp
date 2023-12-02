#include <iostream>
#include <vector>
#include <fstream>

int main() {
    std::vector<std::string> input;
    std::string line;
    std::ifstream fIn("input.txt");
    while (std::getline(fIn, line))
        input.push_back(line);
    fIn.close();

    int sum = 0;

    for (const auto& str : input) {
        std::string firstDigit, lastDigit;
        for (const auto& ch : str)
            if (std::isdigit(ch)) {
                firstDigit = ch;
                break;
            }

        for (auto it = str.rbegin(); it != str.rend(); ++it)
            if (std::isdigit(*it)) {
                lastDigit = *it;
                break;
            }

        sum += std::stoi(firstDigit+lastDigit);
    }

    std::cout << sum << "\n";

    return 0;
}
