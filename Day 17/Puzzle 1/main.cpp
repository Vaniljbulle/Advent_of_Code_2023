#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Point {
    int x, y;

    Point operator+(const Point& other) const {
        return {x + other.x, y + other.y};
    }
};

const Point directions[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

struct State {
    Point position;
    int dir, steps, heat;

    State(Point pos, int d, int s, int h) : position(pos), dir(d), steps(s), heat(h) {}

    bool operator>(const State& other) const {
        return heat > other.heat;
    }
};

bool inBounds(const Point& point, int rows, int cols) {
    return point.x >= 0 && point.x < rows && point.y >= 0 && point.y < cols;
}

int main() {
    vector<string> grid;
    string temp;
    ifstream fIn("../../input.txt");
    while (getline(fIn, temp)) {
        if (temp.empty()) continue;
        grid.push_back(temp);
    }
    fIn.close();

    vector<vector<vector<vector<bool>>>> visited((int)grid.size(), vector<vector<vector<bool>>>((int)grid[0].size(), vector<vector<bool>>(4, vector<bool>(4, false))));

    priority_queue<State, vector<State>, greater<>> frontier;
    frontier.push(State{{0, 0}, -1, 0, 0});

    int heatLoss = INT_MAX;
    while (!frontier.empty()) {
        auto current = frontier.top();
        frontier.pop();

        if (current.position.x == (int)grid.size() - 1 && current.position.y == (int)grid[0].size() - 1) {
            heatLoss = min(heatLoss, current.heat);
            continue;
        }

        for (int i = 0; i < 4; ++i) {
            if (current.dir != -1 && (i == (current.dir + 2) % 4)) continue;

            Point next = current.position + directions[i];
            int totalSteps = (i == current.dir) ? current.steps + 1 : 1;
            if (inBounds(next,(int)grid.size(), (int)grid[0].size()) && totalSteps <= 3 && !visited[next.y][next.x][i][totalSteps]) {
                int newHeat = current.heat + (next.y == 0 && next.x == 0 ? 0 : grid[next.y][next.x] - '0');
                visited[next.y][next.x][i][totalSteps] = true;
                frontier.emplace(next, i, totalSteps, newHeat);
            }
        }
    }

    cout << heatLoss << endl;

    return 0;
}