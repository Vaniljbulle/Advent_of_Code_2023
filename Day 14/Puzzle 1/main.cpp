#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>

struct Stone {
    size_t x, y;
};

int main() {
    std::vector<std::string> input;
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

    size_t load = 0;

    for(auto &stone: stones){
        while (stone.y > 0 && input[stone.y - 1][stone.x] == '.') --stone.y;

        input[stone.y][stone.x] = 'O';
        load += input.size() - stone.y;
    }

    std::cout << load << std::endl;

    return 0;
}
