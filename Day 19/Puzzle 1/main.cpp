#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>
#include <unordered_map>

struct part {
    int x,m,a,s;
    int rating() const {return x+m+a+s;};
};

bool eval(char c, bool lessThan, int val, part &p) {
    if (c == 'x') return lessThan ? p.x < val : p.x > val;
    if (c == 'm') return lessThan ? p.m < val : p.m > val;
    if (c == 'a') return lessThan ? p.a < val : p.a > val;
    if (c == 's') return lessThan ? p.s < val : p.s > val;
}

bool processWork(std::unordered_map<std::string, std::string> &workflow, part &p, const std::string& key) {
    std::string value = workflow[key];
    while (true){
        char c = value[0];
        bool lessThan = value[1] == '<';
        int val = std::stoi(value.substr(2, value.find(':') - 1));
        value = value.substr(value.find(':') + 1);
        std::string next = value.substr(0, value.find(','));
        value = value.substr(value.find(',') + 1);

        if(!eval(c, lessThan, val, p)) {
            if (value[1] == '>' || value[1] == '<') continue;
            next = value;
        }

        if (next[0] == 'A' || next[0] == 'R') return next[0] == 'A';
        return processWork(workflow, p, next);
    }
}

int main() {
    std::unordered_map<std::string, std::string> workflow;
    std::vector<part> parts;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    bool flow = true;
    while (getline(fIn, temp)) {
        if (temp.empty()) flow = false;
        else if (flow){
            std::string key = temp.substr(0, temp.find('{'));
            std::string value = temp.substr(temp.find('{') + 1, temp.find('}') - temp.find('{') - 1);
            workflow[key] = value;
        } else {
            part p;
            p.x = std::stoi(temp.substr(temp.find('=') + 1, temp.find(',') - temp.find('=') - 1));
            temp = temp.substr(temp.find(',') + 1);
            p.m = std::stoi(temp.substr(temp.find('=') + 1, temp.find(',') - temp.find('=') - 1));
            temp = temp.substr(temp.find(',') + 1);
            p.a = std::stoi(temp.substr(temp.find('=') + 1, temp.find(',') - temp.find('=') - 1));
            temp = temp.substr(temp.find(',') + 1);
            p.s = std::stoi(temp.substr(temp.find('=') + 1, temp.find(',') - temp.find('=') - 1));
            parts.push_back(p);
        }

    }
    fIn.close();

    int totalRating = 0;
    for (auto &p: parts) {
        if (processWork(workflow, p, "in")) {
            totalRating += p.rating();
        }
    }

    std::cout << totalRating << std::endl;
    return 0;
}