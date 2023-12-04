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

    std::vector<int> copiesOfCard(input.size(), 1);
    for (int i = 0; i < input.size(); i++){
        std::unordered_set<int> winningNumbers;
        std::vector<int> numbers;
        std::istringstream iss(input[i]);

        // Discard first 2 words
        iss >> temp >> temp;

        while (iss >> temp && temp != "|") winningNumbers.insert(std::stoi(temp));
        while (iss >> temp) numbers.push_back(std::stoi(temp));

        int score = 0;
        for (auto& number : numbers)
            if (winningNumbers.find(number) != winningNumbers.end())
                score++;

        score += i+1;
        for (int j = i+1; j < score; j++)
            copiesOfCard[j] += copiesOfCard[i];

        sum += copiesOfCard[i];
    }

    std::cout << sum << std::endl;

    return 0;
}