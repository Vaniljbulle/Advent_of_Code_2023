#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::string input;
    std::ifstream fIn("../../input.txt");
    std::getline(fIn, input);
    fIn.close();

    int currentValue = 0, sum = 0;
    for(auto &c: input){
        if(c == ',') {
            sum += currentValue;
            currentValue = 0;
            continue;
        }

        currentValue += c;
        currentValue *= 17;
        currentValue %= 256;
    }
    sum += currentValue;

    std::cout << sum << std::endl;

    return 0;
}
