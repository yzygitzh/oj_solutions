/*
 * POJ 2488 - A Knight's Journey
 *
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <string>
#include <map>
#include <cmath>

using namespace std;

int rowNum, colNum; // col:row, A:1
int visited[30][30];
vector<pair<int, int> > path;

int getAbs(int x) {
    return x < 0 ? -x : x;
}

bool isValidStep(int row1, int col1, int row2, int col2) {
    return getAbs(row1 - row2) == 1 && getAbs(col1 - col2) == 2 ||
           getAbs(row1 - row2) == 2 && getAbs(col1 - col2) == 1;
}

void dfs(int row, int col) {
    for (int j = 0; j < colNum; j++) {
        for (int i = 0; i < rowNum; i++) {
            if (!visited[i][j] && isValidStep(row, col, i, j)) {
                visited[i][j] = 1;
                path.push_back(make_pair(i, j));
                dfs(i, j);
                if (path.size() == rowNum * colNum) return;
                path.pop_back();
                visited[i][j] = 0;
            }
        }
    }
}

int main() {
    int caseNum;
    cin >> caseNum;
    for (int k = 0; k < caseNum; k++) {
        cin >> rowNum >> colNum;
        bool found = false;
        for (int j = 0; j < colNum; j++) {
            for (int i = 0; i < rowNum; i++) {
                path.clear();
                memset(visited, 0, sizeof(visited));
                visited[i][j] = 1;
                path.push_back(make_pair(i, j));
                dfs(i, j);
                if (path.size() == rowNum * colNum) {
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        cout << "Scenario #" << k + 1 << ":" << endl;
        if (found) {
            for (auto p : path) {
                cout << char('A' + p.second) << p.first + 1;
            }
        } else {
            cout << "impossible";
        }
        cout << endl << endl;
    }
    return 0;
}

