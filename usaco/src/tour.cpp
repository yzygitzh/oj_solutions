/* Use the slash-star style comments or the system won't see your
   identification information */
/*
ID: yzylive1
TASK: tour
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

ifstream fin ("tour.in");
ofstream fout ("tour.out");

/*
 * F[M][N]: maximum number of cities when A stops at M and B stops at N
 * F[N][M] = F[M][N] = max(F[M][1<=i<=N]+1)
 * where i can go to N
 * note that M < N in recurrence
 */

int N, V;
map<string, int> cityId;
int W[110][110] = {0};
int F[110][110] = {0};

int main() {
    fin >> N >> V;
    for (int i = 0; i < N; i++) {
        string city;
        fin >> city;
        cityId[city] = i;
    }
    for (int i = 0; i < V; i++) {
        string c1, c2;
        fin >> c1 >> c2;
        W[cityId[c1]][cityId[c2]] = 1;
        W[cityId[c2]][cityId[c1]] = 1;
    }
    F[0][0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // j > i
            int maxCity = 0;
            for (int k = 0; k < j; k++) {
                if (W[k][j] && F[i][k]) {
                    int cityNum = F[i][k] + 1;
                    if (cityNum > maxCity) maxCity = cityNum;
                }
            }
            F[i][j] = F[j][i] = maxCity;
            // cout << i << " " << j << " " << maxCity << endl;
        }
    }
    int maxCity = 0;
    for (int i = 0; i < N - 1; i++) {
        if (W[i][N - 1]) {
            int cityNum = F[i][N - 1];
            if (cityNum > maxCity) maxCity = cityNum;
        }
    }
    if (maxCity == 0) fout << 1 << endl;
    else fout << maxCity << endl;
    return 0;
}
