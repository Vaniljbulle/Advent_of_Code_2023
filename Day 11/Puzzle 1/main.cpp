#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

#define EXPANSION 1

struct Point {
    int x, y;
};

int manhattanDistance(const Point& a, const Point& b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

int main() {
    std::vector<std::string> input;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;
        input.push_back(temp);
    }
    fIn.close();

    std::vector<bool> columnEmpty(input[0].size(), true);
    std::unordered_set<int> emptyRows, emptyColumns;
    std::vector<Point> galaxies;

    // Find empty rows
    for (int i = 0; i < input.size(); i++) {
        if(std::all_of(input[i].begin(), input[i].end(), [](char c){ return c == '.'; }))
            emptyRows.insert(i);

        // Empty columns
        for (int j = 0; j < input[i].size(); j++)
            if (input[i][j] == '#') {
                columnEmpty[j] = false;
            }
    }

    // Add empty columns
    for (int i = 0; i < columnEmpty.size(); i++)
        if (columnEmpty[i]) emptyColumns.insert(i);

    // Add galaxies offset with expansion
    int yOffset = 0;
    for (int i = 0; i < input.size(); ++i) {
        if (emptyRows.find(i) != emptyRows.end()) yOffset += EXPANSION;

        int xOffset = 0;
        for (int j = 0; j < input[i].size(); ++j) {
            if (emptyColumns.find(j) != emptyColumns.end()) xOffset += EXPANSION;

            if (input[i][j] == '#') {
                galaxies.push_back({j + xOffset, i + yOffset});
            }
        }
    }

    // Sum that shit using manhattan distance
    int sum = 0;
    for (int i = 0; i < galaxies.size() - 1; ++i) {
        for (int j = i + 1; j < galaxies.size(); ++j) {
            sum += manhattanDistance(galaxies[i], galaxies[j]);
        }
    }
    std::cout << sum << std::endl;

    return 0;
}
