/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: bigbrn
LANG: C++
*/
/* LANG can be C++20 or C++14 for those more recent releases */
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
#include <utility>

#pragma pack(1)
using namespace std;

ifstream fin ("bigbrn.in");
ofstream fout ("bigbrn.out");

int N, T;
char farm[1010][1010] = {0};
int F[1010][1010] = {0};
int maxLen = 0;

int getMin(int x, int y) {
    return x < y ? x : y;
}

int main() {
    fin >> N >> T;
    for (int i = 0; i <= N + 1; i++) {
        for (int j = 0; j <= N + 1; j++) {
            farm[i][j] = '0';
        }
    }
    // init trees on four edges
    for (int i = 0; i <= N + 1; i++) {
        farm[0][i] = farm[N + 1][i] = '1';
        farm[i][0] = farm[i][N + 1] = '1';
    }
    for (int i = 0; i < T; i++) {
        int row, col;
        fin >> row >> col;
        farm[row][col] = '1';
    }

    // init left and up edge
    for (int i = 1; i <= N; i++) {
        if (farm[1][i] == '1') {
            F[1][i] = 0;
        } else {
            F[1][i] = 1;
        }
        if (farm[i][1] == '1') {
            F[i][1] = 0;
        } else {
            F[i][1] = 1;
        }
    }

    for (int i = 2; i <= N; i++) {
        for (int j = 2; j <= N; j++) {
            if (farm[i][j] == '1') continue;
            int upLen = getMin(F[i - 1][j], F[i - 1][j - 1]);
            int leftLen = getMin(F[i][j - 1], F[i - 1][j - 1]);
            F[i][j] = getMin(upLen, leftLen) + 1;
        }
    }
    
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (F[i][j] > maxLen) maxLen = F[i][j];
        }
    }
    
    fout << maxLen << endl;

    return 0;
}
