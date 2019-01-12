/*
 * POJ 1573 - Robot Motion
 *
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

pair<int, int> moveOneStep(pair<int, int> pos, char c) {
    if (c == 'N') pos.first -= 1;
    else if (c == 'W') pos.second -= 1;
    else if (c == 'S') pos.first += 1;
    else pos.second += 1;
    return pos;
}

int main() {
    while (true) {
        int rowNum, colNum, startCol;
        char grid[20][20];
        int visited[20][20] = {0};

        cin >> rowNum >> colNum >> startCol;
        if (rowNum == 0) break;

        string gridLine;
        for (int i = 0; i < rowNum; i++) {
            cin >> gridLine;
            memcpy(grid[i], gridLine.c_str(), gridLine.length());
        }

        pair<int, int> pos = make_pair(0, startCol - 1);
        int step = 1;
        bool outOfBound = false;
        while (!visited[pos.first][pos.second]) {
            visited[pos.first][pos.second] = step;
            pos = moveOneStep(pos, grid[pos.first][pos.second]);
            if (pos.first < 0 || pos.first >= rowNum ||
                pos.second < 0 || pos.second >= colNum) {
                outOfBound = true;
                break;
            }
            step++;
        }

        if (outOfBound) {
            cout << step << " step(s) to exit" << endl;
        } else {
            cout << visited[pos.first][pos.second] - 1
                 << " step(s) before a loop of "
                 << step - visited[pos.first][pos.second]
                 << " step(s)" << endl;
        }
    }
    return 0;
}
