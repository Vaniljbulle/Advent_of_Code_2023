#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

struct Point {
    int x, y;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-(const Point &other) const {
        return {x - other.x, y - other.y};
    }
} const UP = {0, -1}, DOWN = {0, 1}, LEFT = {-1, 0}, RIGHT = {1, 0};

namespace std {
    template<>
    struct hash<Point> {
        std::size_t operator()(const Point &p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
        }
    };
}

void energize(std::unordered_map<Point, std::unordered_set<Point>> &energizedCells, std::pair<Point, Point> &current, const std::vector<std::string> &grid);
bool move(std::unordered_map<Point, std::unordered_set<Point>> &energizedCells, std::pair<Point, Point> &current, const std::vector<std::string> &grid) {
    current.first = current.first + current.second;
    if (current.first.x < 0 || current.first.x >= grid[0].size() || current.first.y < 0 || current.first.y >= grid.size()) {
        return false;
    }

    char cell = grid[current.first.y][current.first.x];
    if (cell == '.') {
        return true;
    }

    Point &direction = current.second;
    if (cell == '\\') {
        direction = (direction == UP) ? LEFT : (direction == DOWN) ? RIGHT : (direction == LEFT) ? UP : DOWN;
    } else if (cell == '/') {
        direction = (direction == UP) ? RIGHT : (direction == DOWN) ? LEFT : (direction == LEFT) ? DOWN : UP;
    } else if (cell == '|' || cell == '-') {
        Point splitDirection = (cell == '|') ? UP : LEFT;
        std::pair<Point, Point> split = {current.first, splitDirection};
        energize(energizedCells, split, grid);
        direction = (cell == '|') ? DOWN : RIGHT;
    }

    return true;
}

void energize(std::unordered_map<Point, std::unordered_set<Point>> &energizedCells, std::pair<Point, Point> &current, const std::vector<std::string> &grid) {
    while (move(energizedCells, current, grid) && energizedCells[current.first].insert(current.second).second);
}

int processLine(const std::vector<std::string>& grid, int index, bool isRow, Point direction) {
    int startIdx = isRow ? 1 : 0;
    int endIdx = isRow ? (grid[0].size() - 1) : grid.size();
    int max = 0;
    for (int i = startIdx; i < endIdx; ++i) {
        std::unordered_map<Point, std::unordered_set<Point>> energizedCells;
        Point position = isRow ? Point{i, index} : Point{index, i};
        std::pair<Point, Point> start = {position - direction, direction};

        energize(energizedCells, start, grid);
        max = std::max(max, (int)energizedCells.size());
    }
    return max;
}

int main() {
    std::vector<std::string> grid;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;
        grid.push_back(temp);
    }
    fIn.close();

    int max = 0;

    max = std::max(max, processLine(grid, 0, true, DOWN));
    max = std::max(max, processLine(grid, 0, false, RIGHT));
    max = std::max(max, processLine(grid, grid[0].size() - 1, false, LEFT));
    max = std::max(max, processLine(grid, grid.size() - 1, true, UP));

    std::cout << max << std::endl;
    return 0;
}
