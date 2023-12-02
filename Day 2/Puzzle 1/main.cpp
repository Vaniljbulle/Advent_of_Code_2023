#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::vector<std::string> input;
    std::string line;
    std::ifstream fIn("input.txt");
    while (std::getline(fIn, line)) {
        input.push_back(line);
    }
    fIn.close();

    int sum = 0;

    for (const auto& gameLine : input) {
        std::stringstream ss(gameLine);
        int gameId;
        std::string gamePrefix, colon;
        ss >> gamePrefix >> gameId >> colon;

        bool isPossible = true;
        std::string subset;
        while (std::getline(ss, subset, ';')) {
            int red = 0, green = 0, blue = 0;
            std::stringstream subsetStream(subset);
            std::string cube;
            while (std::getline(subsetStream, cube, ',')) {
                std::stringstream cubeStream(cube);
                int count;
                char color;
                cubeStream >> count >> color;

                if (color == 'r') red += count;
                else if (color == 'g') green += count;
                else if (color == 'b') blue += count;
            }

            if (red > 12 || green > 13 || blue > 14) {
                isPossible = false;
                break;
            }
        }

        if (isPossible) {
            sum += gameId;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
