#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <climits>

void getSeeds(const std::string &input, std::vector<long long> &seeds) {
    std::string temp;
    std::istringstream iss(input);
    iss >> temp;
    while (iss >> temp) {
        long long seed = stoll(temp);
        seeds.push_back(seed);
    }
}

std::tuple<long long, long long, long long> getTupleRange(const std::string &input) {
    std::istringstream iss(input);
    long long first, second, third;
    iss >> first >> second >> third;
    first = second - first;
    return std::make_tuple(first, second, third);
}


int processMapSection(const std::vector<std::string> &input,
                      int currentIndex,
                      const std::string &nextMapTitle,
                      std::vector<std::tuple<long long, long long, long long>> &mapStorage) {
    for (int j = currentIndex + 1; j < input.size(); ++j) {
        if (input[j] == nextMapTitle) {
            return j - 1;
        }
        mapStorage.emplace_back(getTupleRange(input[j]));
    }
    return -1;
}


long long getNextMapValue(const std::vector<std::tuple<long long, long long, long long>> &map, long long &param) {
    long long result = param;
    for (auto &tuple: map) {
        if (param >= std::get<1>(tuple) && param <= std::get<1>(tuple) + std::get<2>(tuple)) {
            result = param - std::get<0>(tuple);
            break;
        }
    }
    return result;
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

    std::vector<long long> seeds;
    std::vector<std::tuple<long long, long long, long long>> seedToSoil;
    std::vector<std::tuple<long long, long long, long long>> soilToFertilizer;
    std::vector<std::tuple<long long, long long, long long>> fertilizerToWater;
    std::vector<std::tuple<long long, long long, long long>> waterToLight;
    std::vector<std::tuple<long long, long long, long long>> lightToTemperature;
    std::vector<std::tuple<long long, long long, long long>> temperatureToHumidity;
    std::vector<std::tuple<long long, long long, long long>> humidityToLocation;

    getSeeds(input[0], seeds);

    for (int i = 1; i < input.size(); ++i) {
        if (input[i] == "seed-to-soil map:") {
            i = processMapSection(input, i, "soil-to-fertilizer map:", seedToSoil);
        } else if (input[i] == "soil-to-fertilizer map:") {
            i = processMapSection(input, i, "fertilizer-to-water map:", soilToFertilizer);
        } else if (input[i] == "fertilizer-to-water map:") {
            i = processMapSection(input, i, "water-to-light map:", fertilizerToWater);
        } else if (input[i] == "water-to-light map:") {
            i = processMapSection(input, i, "light-to-temperature map:", waterToLight);
        } else if (input[i] == "light-to-temperature map:") {
            i = processMapSection(input, i, "temperature-to-humidity map:", lightToTemperature);
        } else if (input[i] == "temperature-to-humidity map:") {
            i = processMapSection(input, i, "humidity-to-location map:", temperatureToHumidity);
        } else if (input[i] == "humidity-to-location map:") {
            processMapSection(input, i, "", humidityToLocation);
        }
    }

    long long lowestLocation = LLONG_MAX;
    for (auto &seed: seeds) {
        long long prev = getNextMapValue(seedToSoil, seed);
        long long next = getNextMapValue(soilToFertilizer, prev);
        prev = getNextMapValue(fertilizerToWater, next);
        next = getNextMapValue(waterToLight, prev);
        prev = getNextMapValue(lightToTemperature, next);
        next = getNextMapValue(temperatureToHumidity, prev);
        prev = getNextMapValue(humidityToLocation, next);

        lowestLocation = std::min(lowestLocation, prev);
    }

    std::cout << lowestLocation << std::endl;
    return 0;
}
