#undef _GLIBCXX_DEBUG
#pragma GCC optimize("Ofast,inline")
#pragma GCC option("arch=native", "tune=native", "no-zero-upper")

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <mutex>
#include <thread>
#include <functional>
#include <queue>
#include <condition_variable>

// Tried threading part 1 solution but it was still far too slow

std::string createKey(int pos, const std::vector<int> &s, int h) {
    std::string key = std::to_string(pos) + "-";
    for (auto num: s) {
        key += std::to_string(num) + ",";
    }
    key += "k" + std::to_string(h);
    return key;
}

unsigned long long count(const std::string &p, std::vector<int> s, int h, std::unordered_map<std::string, unsigned long long> &memo) {
    if (p.empty()) {
        return s.empty() && h == 0;
    }
    std::string key = createKey(p.size(), s, h);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    unsigned long long n = 0;
    if (p[0] == '#' || p[0] == '?') {
        n += count(p.substr(1), s, h + 1, memo);
    }
    if ((p[0] == '.' || p[0] == '?') && (!s.empty() && s[0] == h || h == 0)) {
        std::vector<int> newS = (h == 0) ? s : std::vector<int>(s.begin() + 1, s.end());
        n += count(p.substr(1), newS, 0, memo);
    }
    memo[key] = n;
    return n;
}

int main() {
    std::vector<std::string> input;
    std::vector<std::vector<int>> arrangements;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        if (temp.empty()) continue;
        std::istringstream iss(temp);
        std::string word;
        std::getline(iss, word, ' ');
        word = word + "?" + word + "?" + word + "?" + word + "?" + word;
        input.push_back(word);

        std::string numbers;
        std::getline(iss, numbers);
        std::istringstream iss2(numbers);
        std::string num;
        std::vector<int> arr;
        while (std::getline(iss2, num, ',')) {
            arr.push_back(std::stoi(num));
        }
        std::vector<int> arr2;
        for (int i = 0; i < 5; ++i) {
            arr2.insert(arr2.end(), arr.begin(), arr.end());
        }
        arrangements.push_back(arr2);
    }
    fIn.close();

    unsigned long long total = 0;
    for (size_t i = 0; i < input.size(); ++i) {
        std::unordered_map<std::string, unsigned long long> memo;
        total += count(input[i] + ".", arrangements[i], 0, memo);
    }

    std::cout << total << std::endl;

    return 0;
}
