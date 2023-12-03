#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void replaceWithDots(std::vector<std::string> &grid, int row, int col, int len) {
    for (int i = 0; i < len; ++i) {
        grid[row][col + i] = '.';
    }
}

std::pair<int, int> validPartNumber(const std::vector<std::string> &grid, int row, int col, int len) {
    auto isStarCell = [&](int r, int c) {
        return r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size() && grid[r][c] == '*';
    };

    std::pair<int, int> starPos = {-1, -1};

    // Check left and right
    if (isStarCell(row, col - 1)) return {row, col - 1};
    if (isStarCell(row, col + len)) return {row, col + len};

    // Check diagonally, above, and below
    for (int offset = -1; offset <= len; ++offset) {
        if (isStarCell(row - 1, col + offset)) return {row - 1, col + offset};
        if (isStarCell(row + 1, col + offset)) return {row + 1, col + offset};
    }

    return starPos;
}

constexpr static int directions[8][2] = {{0,-1}, // left
                                         {0,1}, // right
                                         {-1,0}, // above
                                         {1,0}, // below
                                         {-1,-1}, // diagonally above left
                                         {-1,1}, // diagonally above right
                                         {1,-1}, // diagonally below left
                                         {1,1}}; // diagonally below right

bool isValid(std::vector<std::string> &grid, int row, int col) {
    for (const auto &dir: directions) {
        int y = row + dir[0], x = col + dir[1];

        if (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size() && isdigit(grid[y][x])) {
            return false;
        }
    }

    return true;
}

int findSurroundingInteger(std::vector<std::string> &grid, int row, int col) {
    for (const auto &dir: directions) {
        int y = row + dir[0], x = col + dir[1];

        if (y >= 0 && y < grid.size() && x >= 0 && x < grid[0].size() && isdigit(grid[y][x])) {
            int len = 0;
            while (--x && isdigit(grid[y][x])) {}
            if (x != 0) ++x;

            while (isdigit(grid[y][x + len])) ++len;

            int gear = std::stoi(grid[y].substr(x, len));
            replaceWithDots(grid, y, x, len);

            auto alone = isValid(grid, row, col);
            if (!alone) gear = -1;
            return gear;
        }
    }

    return -1;
}


int main() {
    std::vector<std::string> input;
    std::string inputLine;
    std::ifstream fIn("input.txt");
    while (std::getline(fIn, inputLine)) {
        input.push_back(inputLine);
    }
    fIn.close();

    size_t sum = 0;

    for (int row = 0; row < input.size(); ++row) {
        for (int col = 0; col < input[row].size(); ++col) {
            if (isdigit(input[row][col])) {
                int len = 0;
                while (col + len < input[row].size() && isdigit(input[row][col + len]))
                    ++len;

                auto starPos = validPartNumber(input, row, col, len);
                if (starPos.first != -1) {
                    size_t gear1 = std::stoi(input[row].substr(col, len));
                    replaceWithDots(input, row, col, len);
                    size_t gear2 = findSurroundingInteger(input, starPos.first, starPos.second);
                    if (gear2 != -1) sum += gear1 * gear2;
                }
                col += len - 1;
            }
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
