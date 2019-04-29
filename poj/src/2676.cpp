/*
 * POJ 2676 - Sudoku
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

char sudoku[10][10];
int rowVisited[10][10], colVisited[10][10], blockVisited[10][10];

bool dfs(int row, int col) {
    int blockId = row / 3 * 3 + col / 3;
    if (blockId > 8) return true;
    int nextRow = (row * 9 + col + 1) / 9;
    int nextCol = (row * 9 + col + 1) % 9;
    if (sudoku[row][col] == '0') {
        for (int i = 1; i <= 9; i++) {
            if (rowVisited[row][i] || colVisited[col][i] || blockVisited[blockId][i]) {
                continue;
            }
            rowVisited[row][i] = colVisited[col][i] = blockVisited[blockId][i] = 1;
            sudoku[row][col] = '0' + i;
            if (dfs(nextRow, nextCol)) return true;
            sudoku[row][col] = '0';
            rowVisited[row][i] = colVisited[col][i] = blockVisited[blockId][i] = 0;
        }
        return false;
    } else {
        return dfs(nextRow, nextCol);
    }
}

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        memset(rowVisited, 0, sizeof(rowVisited));
        memset(colVisited, 0, sizeof(colVisited));
        memset(blockVisited, 0, sizeof(blockVisited));
        for (int i = 0; i < 9; i++) {
            cin >> sudoku[i];
            for (int j = 0; j < 9; j++) {
                rowVisited[i][sudoku[i][j] - '0'] = 1;
                colVisited[j][sudoku[i][j] - '0'] = 1;
                int blockId = i / 3 * 3 + j / 3;
                blockVisited[blockId][sudoku[i][j] - '0'] = 1;
            }
        }
        dfs(0, 0);
        for (int i = 0; i < 9; i++) {
            cout << sudoku[i] << endl;
        }
    }
    return 0;
}

