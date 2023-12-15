#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

#define CYCLES 1000000000

// 1000
// 1000000

struct Stone {
    size_t x, y;
};

int cycle(const std::vector<Stone> &stones){
    int sumX = 0, sumY = 0;
    for (auto &stone: stones) {
        sumX += stone.x;
        sumY += stone.y;
    }
    return sumX + sumY;
}

int main() {
    std::vector<std::string> input, copy;
    std::vector<Stone> stones;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;

        for (size_t i = 0; i < temp.size(); ++i) {
            if (temp[i] == 'O') {
                stones.push_back({i, input.size()});
                temp[i] = '.';
            }
        }
        input.push_back(temp);
    }
    fIn.close();

    std::vector<int> cycles;
    bool cycleFound = false;
    size_t cycleLength = 0;
    for(size_t i = 0; i < CYCLES; ++i) {
        if(!cycleFound) {
            int currentCycle = cycle(stones);
            if (std::find(cycles.begin(), cycles.end(), currentCycle) != cycles.end()) {
                auto it = std::find(cycles.begin(), cycles.end(), currentCycle);
                size_t startOfCycle = std::distance(cycles.begin(), it);
                std::cout << cycleLength << std::endl;

                if (i - startOfCycle == cycleLength) {
                    cycleFound = true;
                    i += (CYCLES - i) / cycleLength * cycleLength;
                } else cycleLength = i - startOfCycle;
            }
            cycles.push_back(cycle(stones));
        }

        // North
        std::sort(stones.begin(), stones.end(), [](const Stone &a, const Stone &b) { return a.y < b.y; });
        copy = input;
        for(auto &stone: stones){
            while (stone.y > 0 && copy[stone.y - 1][stone.x] == '.') --stone.y;
            copy[stone.y][stone.x] = 'O';
        }
        // West
        std::sort(stones.begin(), stones.end(), [](const Stone &a, const Stone &b) { return a.x < b.x; });
        copy = input;
        for(auto &stone: stones){
            while (stone.x > 0 && copy[stone.y][stone.x - 1] == '.') --stone.x;
            copy[stone.y][stone.x] = 'O';
        }
        // South
        std::sort(stones.begin(), stones.end(), [](const Stone &a, const Stone &b) { return a.y > b.y; });
        copy = input;
        for(auto &stone: stones){
            while (stone.y < input.size() - 1 && copy[stone.y + 1][stone.x] == '.') ++stone.y;
            copy[stone.y][stone.x] = 'O';
        }
        // East
        std::sort(stones.begin(), stones.end(), [](const Stone &a, const Stone &b) { return a.x > b.x; });
        copy = input;
        for(auto &stone: stones){
            while (stone.x < input[0].size() - 1 && copy[stone.y][stone.x + 1] == '.') ++stone.x;
            copy[stone.y][stone.x] = 'O';
        }
    }

    int load = 0;
    for (auto &stone: stones) {
        load += input.size() - stone.y;
    }
    std::cout << load << std::endl;

    return 0;
}