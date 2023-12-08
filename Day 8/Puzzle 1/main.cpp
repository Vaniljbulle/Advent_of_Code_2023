#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <regex>

int main() {
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::string temp, instructions;
    std::ifstream fIn("../../input.txt");
    std::getline(fIn, instructions);
    std::regex r("[A-Z]{3}");
    std::smatch match;
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;

        std::vector<std::string> matches;
        while (std::regex_search(temp, match, r)) {
            for (auto m : match) matches.push_back(m);
            temp = match.suffix().str();
        }
        nodes[matches[0]] = std::make_pair(matches[1], matches[2]);
    }
    fIn.close();

    int steps = 0;
    std::string currentNode = "AAA";
    for (int i = 0; i < instructions.size(); ++i) {
        if (instructions[i] == 'L') currentNode = nodes[currentNode].first;
        else currentNode = nodes[currentNode].second;
        ++steps;

        if (currentNode == "ZZZ") break;
        else if (i == instructions.size() - 1) i = -1;
    }
    std::cout << steps << std::endl;
    return 0;
}
