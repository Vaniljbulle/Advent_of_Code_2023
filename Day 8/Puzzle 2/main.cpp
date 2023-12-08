#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <numeric>

int main() {
    std::unordered_map<std::string, std::pair<std::string, std::string>> nodes;
    std::vector<std::string> startingNodes;
    std::string temp, instructions;
    std::ifstream fIn("../../input.txt");
    std::getline(fIn, instructions);
    std::regex r("[A-Z0-9]{3}");
    std::smatch match;
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;

        std::vector<std::string> matches;
        while (std::regex_search(temp, match, r)) {
            for (auto m: match) matches.push_back(m);
            temp = match.suffix().str();
        }
        if (matches[0][2] == 'A') startingNodes.push_back(matches[0]);
        nodes[matches[0]] = std::make_pair(matches[1], matches[2]);
    }
    fIn.close();

    std::vector<int> steps(startingNodes.size(), 0);
    for (int j = 0; j < startingNodes.size(); ++j) {
        for (int i = 0; i < instructions.size(); ++i) {
            if (instructions[i] == 'L') startingNodes[j] = nodes[startingNodes[j]].first;
            else startingNodes[j] = nodes[startingNodes[j]].second;

            ++steps[j];
            if (i == instructions.size() - 1) i = -1;
            if (startingNodes[j][2] == 'Z') break;
        }
    }

    long long lcm = steps[0];
    for (int i = 1; i < steps.size(); ++i)
        lcm = std::lcm(lcm, steps[i]);

    std::cout << lcm << std::endl;

    return 0;
}
