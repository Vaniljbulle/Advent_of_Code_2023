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

    bool operator==(const Point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point &other) const {
        return !(*this == other);
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }
} UP{0, -2}, DOWN{0, 2}, LEFT{-2, 0}, RIGHT{2, 0};

struct PointHash {
    size_t operator()(const Point &p) const {
        return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);
    }
};

bool isValid(Point dir, const std::vector<std::string> &grid, const Point &p) {
    char from = grid[p.y][p.x];
    char to = grid[p.y + dir.y][p.x + dir.x];

    if (dir == UP && (from == 'S' || from == 'L' || from == 'J' || from == '|'))
        return to == '|' || to == 'F' || to == '7' || to == 'S';
    if (dir == DOWN && (from == 'S' || from == '7' || from == 'F' || from == '|'))
        return to == '|' || to == 'L' || to == 'J' || to == 'S';
    if (dir == LEFT && (from == 'S' || from == 'J' || from == '7' || from == '-'))
        return to == '-' || to == 'F' || to == 'L' || to == 'S';
    if (dir == RIGHT && (from == 'S' || from == 'L' || from == 'F' || from == '-'))
        return to == '-' || to == 'J' || to == '7' || to == 'S';


    return false;
}

std::vector<Point> getNeighbors(const Point &p, const std::vector<std::string> &grid) {
    std::vector<Point> neighbors;
    if (p.y > 1 && isValid(UP, grid, p)) neighbors.push_back(p + UP);
    if (p.y < grid.size() - 2 && isValid(DOWN, grid, p)) neighbors.push_back(p + DOWN);
    if (p.x > 1 && isValid(LEFT, grid, p)) neighbors.push_back(p + LEFT);
    if (p.x < grid[p.y].size() - 2 && isValid(RIGHT, grid, p)) neighbors.push_back(p + RIGHT);

    return neighbors;
}

void floodFill(std::vector<std::vector<bool>> &reachable, const std::vector<std::string> &grid,
               const std::unordered_set<Point, PointHash> &visited, int startX, int startY) {
    std::queue<Point> pointsQueue;
    pointsQueue.push({startX, startY});

    while (!pointsQueue.empty()) {
        Point p = pointsQueue.front();
        pointsQueue.pop();

        if (p.x < 0 || p.x >= grid[0].size() || p.y < 0 || p.y >= grid.size() || reachable[p.y][p.x] ||
            visited.find(p) != visited.end()) {
            continue;
        }

        reachable[p.y][p.x] = true;

        pointsQueue.push({p.x + 1, p.y});
        pointsQueue.push({p.x - 1, p.y});
        pointsQueue.push({p.x, p.y + 1});
        pointsQueue.push({p.x, p.y - 1});
    }
}

std::unordered_set<Point, PointHash>
findEnclosedCells(const std::vector<std::string> &grid, const std::unordered_set<Point, PointHash> &visited) {
    int rows = grid.size();
    int cols = grid[0].size();
    std::vector<std::vector<bool>> reachable(rows, std::vector<bool>(cols, false));
    std::unordered_set<Point, PointHash> enclosedCells;

    floodFill(reachable, grid, visited, 0, 0);

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            if (!reachable[y][x] && visited.find(Point{x, y}) == visited.end())
                enclosedCells.insert(Point{x, y});

    return enclosedCells;
}

std::vector<std::string> stretchGrid(const std::vector<std::string> &originalGrid) {
    int rows = originalGrid.size();
    int cols = originalGrid[0].size();
    std::vector<std::string> stretchedGrid(rows * 2, std::string(cols * 2, 'g'));

    for (int y = 0; y < rows; ++y)
        for (int x = 0; x < cols; ++x)
            stretchedGrid[y * 2][x * 2] = originalGrid[y][x];

    return stretchedGrid;
}

std::unordered_set<Point, PointHash> findLoop(const std::vector<std::string> &grid, const Point &start) {
    std::unordered_set<Point, PointHash> visited;
    std::vector<Point> path;
    Point current = start;

    do {
        visited.insert(current);
        path.push_back(current);
        std::vector<Point> neighbors = getNeighbors(current, grid);

        Point next{};
        bool foundNext = false;
        for (const auto &neighbor: neighbors) {
            Point midPoint{(current.x + neighbor.x) / 2, (current.y + neighbor.y) / 2};
            visited.insert(midPoint);
            if (visited.find(neighbor) == visited.end()) {
                next = neighbor;
                foundNext = true;
                break;
            }
        }

        if (!foundNext) {
            return visited;
        }

        current = next;
    } while (current != start);

    //return -1;
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
            start = {index, (int) (grid.size())};
        }
        grid.push_back(temp);
    }
    fIn.close();

    auto stretchedGrid = stretchGrid(grid);
    start = {start.x * 2, start.y * 2};

    auto visited = findLoop(stretchedGrid, start);
    auto enclosed = findEnclosedCells(stretchedGrid, visited);

    int enclosedCount = 0;
    for (const auto &p: enclosed)
        if (stretchedGrid[p.y][p.x] != 'g')
            ++enclosedCount;

    std::cout << enclosedCount << std::endl;
    return 0;
}
