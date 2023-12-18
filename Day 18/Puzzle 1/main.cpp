#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

struct Point {
    int x, y;
};

std::vector<Point> processInstructions(const std::vector<std::pair<char, int>> &instructions) {
    Point current = {0, 0};
    std::vector<Point> vertices;
    vertices.push_back(current);
    for (const auto &instruction: instructions) {
        if (instruction.first == 'U') current.y += instruction.second;
        else if (instruction.first == 'D') current.y -= instruction.second;
        else if (instruction.first == 'L') current.x -= instruction.second;
        else if (instruction.first == 'R') current.x += instruction.second;

        vertices.push_back(current);
    }

    return vertices;
}

int manhattanDistance(const Point &a, const Point &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int area(const std::vector<Point> &vertices) {
    int i = 0, b = 0;

    for (size_t v = 0; v < vertices.size(); v++) {
        size_t j = (v + 1) % vertices.size();
        i += (vertices[v].x * vertices[j].y) - (vertices[j].x * vertices[v].y);
        b += manhattanDistance(vertices[v], vertices[j]);
    }

    i = std::abs(i / 2);
    return i + (b / 2) + 1;
}

int main() {
    std::vector<std::pair<char, int>> instructions;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (getline(fIn, temp)) {
        if (temp.empty()) continue;
        instructions.emplace_back(temp[0], std::stoi(temp.substr(1)));
    }
    fIn.close();

    auto vertices = processInstructions(instructions);
    std::cout << area(vertices) << std::endl;

    return 0;
}