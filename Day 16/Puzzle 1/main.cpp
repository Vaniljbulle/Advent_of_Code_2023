#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct Point {
    int x, y;

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
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
    while (energizedCells[current.first].insert(current.second).second && move(energizedCells, current, grid));
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

    std::pair<Point, Point> start = {{0, 0}, DOWN}; // '\' at 0,0 for my input
    std::unordered_map<Point, std::unordered_set<Point>> energizedCells;
    energize(energizedCells, start, grid);

    std::cout << energizedCells.size() << std::endl;

    return 0;
}
