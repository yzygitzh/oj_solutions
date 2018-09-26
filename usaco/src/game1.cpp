/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: game1
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

ifstream fin ("game1.in");
ofstream fout ("game1.out");

/*
 * min-max search, limit opponent's upper bound
 * because best possible opponent tends to find best solution
 * for him in search tree
 */

int N;
int num[110] = {0};
int sum[110][110] = {0};
int memo[110][110] = {0};

void calcSum() {
    for (int i = 0; i < N; i++) {
        sum[i][i] = num[i];
    }
    for (int i = 2; i <= N; i++) {
        for (int j = 0; j + i - 1 < N; j++) {
            sum[j][j + i - 1] = sum[j][j] + sum[j + 1][j + i - 1];
        }
    }
}

int minMax(int lp, int rp) {
    if (lp == rp) return num[lp];
    if (memo[lp][rp]) return memo[lp][rp];
    int leftOppo = minMax(lp + 1, rp);
    int rightOppo = minMax(lp, rp - 1);
    // choose low bound for max oppo value
    if (leftOppo < rightOppo) {
        memo[lp][rp] = sum[lp][rp] - leftOppo;
    } else {
        memo[lp][rp] = sum[lp][rp] - rightOppo;
    }
    return memo[lp][rp];
}

int main() {
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> num[i];
    }
    calcSum();

    int p1Score = minMax(0, N - 1);
    fout << p1Score << " " << sum[0][N - 1] - p1Score << endl;
    return 0;
}

