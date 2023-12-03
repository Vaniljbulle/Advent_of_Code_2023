#include <iostream>
#include <vector>
#include <fstream>
#include <string>

bool validPartNumber(const std::vector<std::string>& grid, int row, int col, int len) {
    // Lambda love
    auto isAdjacentCellInvalid = [&](int r, int c) {
        return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] != '.';
    };

    // left and right
    if (isAdjacentCellInvalid(row, col - 1) || isAdjacentCellInvalid(row, col + len)) return true;

    // diagonally, above, below
    for (int offset = -1; offset <= len; ++offset)
        if (isAdjacentCellInvalid(row - 1, col + offset) || isAdjacentCellInvalid(row + 1, col + offset))
            return true;

    return false;
}


int main() {
    std::vector<std::string> input;
    std::string inputLine;
    std::ifstream fIn("input.txt");
    while (std::getline(fIn, inputLine)) {
        input.push_back(inputLine);
    }
    fIn.close();

    int sum = 0;

    for (int row = 0; row < input.size(); ++row) {
        for (int col = 0; col < input[row].size(); ++col) {
            if (isdigit(input[row][col])) {
                int len = 0;
                while (col + len < input[row].size() && isdigit(input[row][col + len]))
                    ++len;

                if (validPartNumber(input, row, col, len))
                    sum += std::stoi(input[row].substr(col, len));

                col += len - 1;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}