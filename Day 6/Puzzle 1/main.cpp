#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <climits>
#include <valarray>
#include <cmath>

int main() {
    std::vector<std::string> input;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;
        input.push_back(temp);
    }
    fIn.close();


    std::stringstream ssTimes(input[0]); ssTimes >> temp;
    std::stringstream ssDistances(input[1]); ssDistances >> temp;

    std::vector<int> times, distances;
    int value;
    while (ssTimes >> value) times.push_back(value);
    while (ssDistances >> value) distances.push_back(value);

    int product = 1;

    // time = t, distance = d, time button held down = h
    // d = h * (t - h)
    // h^2 - ht + d = 0, solve for h

    for (int i = 0; i < times.size(); ++i) {
        double t = times[i];
        double d = distances[i] + 1;
        double dis = t * t - 4 * d;
        double h1 = (t + std::sqrt(dis)) / 2;
        double h2 = (t - std::sqrt(dis)) / 2;

        int lower_bound = std::max(0, (int)(std::ceil(h2)));
        int upper_bound = std::min(t, (std::floor(h1)));
        product *= (upper_bound - lower_bound + 1);
    }


    std::cout << product << std::endl;
    return 0;
}
