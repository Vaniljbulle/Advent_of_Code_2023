#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int boxHash(std::string &input) {
    int currentValue = 0;
    for(auto &c: input){
        currentValue += c;
        currentValue *= 17;
        currentValue %= 256;
    }
    return currentValue;
}

void replaceOrEmplace(std::vector<std::pair<std::string, int>> &box, std::string &key, int value) {
    bool replaced = false;
    for(auto &it : box)
        if(it.first == key) {
            it.second = value;
            replaced = true;
            break;
        }
    if (!replaced) box.emplace_back(key, value);
}

void remove(std::vector<std::pair<std::string, int>> &box, std::string &key) {
    for(auto it = box.begin(); it != box.end(); ++it)
        if(it->first == key) {
            box.erase(it);
            break;
        }
}

int getFocusingPower(const std::vector<std::vector<std::pair<std::string, int>>> &boxes) {
    int fp = 0;
    for(int box = 0; box < boxes.size(); ++box){
        if(boxes[box].empty()) continue;
        for (int i = 0; i < boxes[box].size(); ++i)
            fp += (box+1) * (i+1) * boxes[box][i].second;
    }
    return fp;
}

int main() {
    std::string input;
    std::ifstream fIn("../../input.txt");
    std::getline(fIn, input);
    fIn.close();

    std::string current;
    std::vector<std::vector<std::pair<std::string, int>>> boxes(256);
    for(int c = 0; c < input.size(); ++c){
        if(input[c] == ',') {
            current = "";
            continue;
        } else if(input[c] == '=') {
            replaceOrEmplace(boxes[boxHash(current)], current, input[c+1] - '0');
            continue;
        } else if(input[c] == '-') {
            remove(boxes[boxHash(current)], current);
            continue;
        }
        current += input[c];
    }

    std::cout << getFocusingPower(boxes) << std::endl;

    return 0;
}
