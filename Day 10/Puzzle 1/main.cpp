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
#include <unordered_set>
#include <unordered_map>
#include <queue>

struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
} UP{0, -1}, DOWN{0, 1}, LEFT{-1, 0}, RIGHT{1, 0};

struct PointHash {
    size_t operator()(const Point& p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

bool isValid(Point dir, const std::vector<std::string>& grid, const Point& p) {
    static std::unordered_map<Point, std::pair<std::string, std::string>, PointHash> validChars = {
            {UP, {"SLJ|", "|F7"}},
            {DOWN, {"S7F|", "|LJ"}},
            {LEFT, {"SJ7-", "-FL"}},
            {RIGHT, {"SLF-", "-J7"}}
    };

    char from = grid[p.y][p.x];
    char to = grid[p.y + dir.y][p.x + dir.x];

    if (validChars.count(dir) > 0 && validChars[dir].first.find(from) != std::string::npos)
        return validChars[dir].second.find(to) != std::string::npos;

    return false;
}

std::vector<Point> getNeighbors(const Point& p, const std::vector<std::string>& grid) {
    std::vector<Point> neighbors;
    if (p.y > 0 && isValid(UP, grid, p)) neighbors.push_back(p + UP);
    if (p.y < grid.size() - 1 && isValid(DOWN, grid, p)) neighbors.push_back(p + DOWN);
    if (p.x > 0 && isValid(LEFT, grid, p)) neighbors.push_back(p + LEFT);
    if (p.x < grid[p.y].size() - 1 && isValid(RIGHT, grid, p)) neighbors.push_back(p + RIGHT);

    return neighbors;
}

int findLoop(const std::vector<std::string>& grid, const Point& start) {
    std::unordered_set<Point, PointHash> visited;
    std::vector<Point> path;
    Point current = start;

    do {
        visited.insert(current);
        path.push_back(current);
        std::vector<Point> neighbors = getNeighbors(current, grid);

        Point next{};
        bool foundNext = false;
        for (const auto& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                next = neighbor;
                foundNext = true;
                break;
            }
        }

        // End of loop
        if (!foundNext) return path.size();

        current = next;
    } while (current != start);

    return -1;
}

int main() {
    std::vector<std::string> grid;
    Point start{};
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;
        if (temp.find('S') != std::string::npos) {
            int index = temp.find('S');
            start = {index, (int)(grid.size())};
        }
        grid.push_back(temp);
    }
    fIn.close();

    std::cout << findLoop(grid, start) / 2 << std::endl;

    return 0;
}
