/*
 * POJ 1321 - 棋盘问题
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

int N, K, caseCnt;
char board[10][10];
int visitedCols[10];

void dfs(int rest, int row) {
    if (rest == 0) caseCnt++;
    if (row >= N) return;
    for (int i = row; i <= N - rest; i++) {
        for (int j = 0; j < N; j++) {
            if (!visitedCols[j] && board[i][j] == '#') {
                visitedCols[j] = 1;
                dfs(rest - 1, i + 1);
                visitedCols[j] = 0;
            }
        }
    }
}

int main() {
    while (true) {
        cin >> N >> K;
        if (N == -1 && K == -1) break;
        for (int i = 0; i < N; i++) {
            cin >> board[i];
        }
        caseCnt = 0;
        memset(visitedCols, 0, sizeof(visitedCols));
        dfs(K, 0);
        cout << caseCnt << endl;
    }
    return 0;
}

