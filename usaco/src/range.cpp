/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: range
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

using namespace std;

ifstream fin ("range.in");
ofstream fout ("range.out");

/*
 * F[M][N]: sum of (0,0) to (M,N)
 * F[M][N] = F[M-1][N] + F[M][N-1] - F[M-1][N-1] + field[M][N]
 */

int N;
int F[300][300] = {0};
char field[300][300];
int squareCnt[300] = {0};

int main() {
    fin >> N;
    string fieldLine;
    for (int i = 0; i < N; i++) {
        fin >> fieldLine;
        memcpy(field[i], fieldLine.c_str(), N);
    }

    int hSum = 0, vSum = 0;
    for (int i = 0; i < N; i++) {
        if (field[0][i] == '1') hSum++;
        F[0][i] = hSum;
        if (field[i][0] == '1') vSum++;
        F[i][0] = vSum;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < N; j++) {
            F[i][j] = F[i - 1][j] + F[i][j - 1] - F[i - 1][j - 1];
            if (field[i][j] == '1') F[i][j]++;
            // cout << F[i][j] << " ";
        }
        // cout << endl;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i >= 1 && j >= 1) {
                if (i > j && F[i][j] - F[i - j - 1][j] == (j + 1) * (j + 1)) squareCnt[j + 1]++;
                else if (i == j && F[i][j] == (i + 1) * (i + 1)) squareCnt[i + 1]++;
                else if (i < j && F[i][j] - F[i][j - i - 1] == (i + 1) * (i + 1)) squareCnt[i + 1]++;
            }
            for (int k = 2; k <= i && k <= j; k++) {
                if (F[i][j] - F[i - k][j] - F[i][j - k] + F[i - k][j - k] == k * k) {
                    squareCnt[k]++;
                }
            }
        }
    }
    for (int i = 2; i <= N; i++) {
        if (squareCnt[i] > 0) fout << i << " " << squareCnt[i] << endl;
    }
    return 0;
}

