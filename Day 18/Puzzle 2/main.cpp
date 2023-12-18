#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>
#include <regex>

struct Point {
    long long x, y;
};

std::vector<Point> processInstructions(const std::vector<std::pair<int, long long>> &instructions) {
    Point current = {0, 0};
    std::vector<Point> vertices;
    vertices.push_back(current);
    for (const auto &instruction: instructions) {
        if (instruction.first == 3) current.y += instruction.second;
        else if (instruction.first == 1) current.y -= instruction.second;
        else if (instruction.first == 2) current.x -= instruction.second;
        else if (instruction.first == 0) current.x += instruction.second;

        vertices.push_back(current);
    }

    return vertices;
}

long long manhattanDistance(const Point &a, const Point &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

long long area(const std::vector<Point> &vertices) {
    long long i = 0, b = 0;

    for (size_t v = 0; v < vertices.size(); v++) {
        size_t j = (v + 1) % vertices.size();
        i += (vertices[v].x * vertices[j].y) - (vertices[j].x * vertices[v].y);
        b += manhattanDistance(vertices[v], vertices[j]);
    }

    i = std::abs(i / 2);
    return i + (b / 2) + 1;
}

int main() {
    std::vector<std::pair<int, long long>> instructions;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    std::regex reg("#([0-9a-fA-F]{6})");
    std::smatch match;
    while (getline(fIn, temp)) {
        if (temp.empty()) continue;
        if (std::regex_search(temp, match, reg)) {
            temp = match[1];
            instructions.emplace_back(std::stoi(temp.substr(temp.size() - 1, temp.size())),
                                      std::stoll(temp.substr(0, temp.size() - 1), nullptr, 16));
        }
    }
    fIn.close();

    auto vertices = processInstructions(instructions);
    std::cout << area(vertices) << std::endl;

    return 0;
}