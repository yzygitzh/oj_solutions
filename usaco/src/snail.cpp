/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: snail
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

using namespace std;

ifstream fin ("snail.in");
ofstream fout ("snail.out");

int N, B;
char grid[130][130] = {0};

int maxLen = 0;

bool dirOK(int row, int col, int dir) {
    return dir == 0 && row - 1 >= 0 && grid[row - 1][col] == '.' ||
           dir == 1 && col + 1 < N && grid[row][col + 1] == '.' ||
           dir == 2 && row + 1 < N && grid[row + 1][col] == '.' ||
           dir == 3 && col - 1 >= 0 && grid[row][col - 1] == '.';
}

bool dirEnd(int row, int col, int dir) {
    return dir == 0 && row - 1 >= 0 && grid[row - 1][col] == '*' ||
           dir == 1 && col + 1 < N && grid[row][col + 1] == '*' ||
           dir == 2 && row + 1 < N && grid[row + 1][col] == '*' ||
           dir == 3 && col - 1 >= 0 && grid[row][col - 1] == '*';
}

void DFS(int row, int col, int len, int dir) {
    // cout << row << " " << col << " " << len << " " << dir << endl;
    if (len > maxLen) {
        maxLen = len;
    }
    if (dirEnd(row, col, dir)) return;
    if (dirOK(row, col, 0) &&
        (dir == 0 ||
         dir == 1 && !dirOK(row, col, 1) ||
         dir == 3 && !dirOK(row, col, 3))) {
        grid[row][col] = '*';
        DFS(row - 1, col, len + 1, 0);
        grid[row][col] = '.';
    }
    if (dirOK(row, col, 1) &&
        (dir == 1 ||
         dir == 0 && !dirOK(row, col, 0) ||
         dir == 2 && !dirOK(row, col, 2))) {
        grid[row][col] = '*';
        DFS(row, col + 1, len + 1, 1);
        grid[row][col] = '.';
    }
    if (dirOK(row, col, 2) &&
        (dir == 2 ||
         dir == 1 && !dirOK(row, col, 1) ||
         dir == 3 && !dirOK(row, col, 3))) {
        grid[row][col] = '*';
        DFS(row + 1, col, len + 1, 2);
        grid[row][col] = '.';
    }
    if (dirOK(row, col, 3) &&
        (dir == 3 ||
         dir == 0 && !dirOK(row, col, 0) ||
         dir == 2 && !dirOK(row, col, 2))) {
        grid[row][col] = '*';
        DFS(row, col - 1, len + 1, 3);
        grid[row][col] = '.';
    }
}

int main() {
    string inputLine;
    char colChar;
    fin >> N >> B;
    getline(fin, inputLine);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = '.';
        }
    }
    for (int i = 0; i < B; i++) {
        int row, col;
        fin >> colChar;
        col = colChar - 'A';
        fin >> row;
        grid[row - 1][col] = '#';
        getline(fin, inputLine);
    }
    DFS(0, 0, 1, 1);
    DFS(0, 0, 1, 2);
    fout << maxLen << endl;
    return 0;
}
