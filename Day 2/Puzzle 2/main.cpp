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

    int powerOfSet = 0;

    for (const auto& gameLine : input) {
        std::stringstream ss(gameLine);
        int gameId;
        std::string gamePrefix, colon;
        ss >> gamePrefix >> gameId >> colon;

        std::string subset;

        int red = 0, green = 0, blue = 0;
        while (std::getline(ss, subset, ';')) {
            std::stringstream subsetStream(subset);
            std::string cube;
            while (std::getline(subsetStream, cube, ',')) {
                std::stringstream cubeStream(cube);
                int count;
                char color;
                cubeStream >> count >> color;

                if (color == 'r' && count > red) red = count;
                else if (color == 'g' && count > green) green = count;
                else if (color == 'b' && count > blue) blue = count;
            }
        }
        powerOfSet += red * green * blue;
    }

    std::cout << powerOfSet << std::endl;

    return 0;
}
