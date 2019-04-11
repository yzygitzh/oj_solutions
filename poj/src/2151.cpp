/*
 * POJ 2151 - Check the difficulty of problems
 *
 */

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

// F[m][n]: probability s.t. n of the first m problem are solved
// F[m][n] = F[m-1][n]*(1-p(m))+F[m-1][n-1]*p(m)
// m >= n
double F[40][40];
// P[m][n]: probability s.t. the m-th team solved n problems
double P[1010][40];
double currP[40];
int M, T, N;

int main() {
    while (cin >> M >> T >> N) {
        if (M == 0 && T == 0 && N == 0) break;
        for (int i = 0; i < T; i++) {
            for (int j = 0; j < M; j++) {
                cin >> currP[j];
            }
            // initialize F
            F[0][0] = 1.0;
            for (int j = 1; j <= M; j++) {
                F[j][0] = F[j - 1][0] * (1 - currP[j - 1]);
            }
            // do DP on F
            for (int j = 1; j <= M; j++) {
                for (int k = 1; k <= j; k++) {
                    F[j][k] = F[j - 1][k - 1] * currP[j - 1];
                    if (j - 1 >= k) {
                        F[j][k] += F[j - 1][k] * (1 - currP[j - 1]);
                    }
                }
            }
            // copy F to P
            for (int j = 0; j <= M; j++) {
                P[i][j] = F[M][j];
            }
        }
        double nonZeroP = 1.0, haveChampionP = 0.0;
        for (int i = 0; i < T; i++) {
            double currNonZeroP = 1.0 - P[i][0];
            double currHaveChampionP = 0.0;
            for (int j = N; j <= M; j++) {
                currHaveChampionP += P[i][j];
            }
            haveChampionP = haveChampionP * currNonZeroP + (nonZeroP - haveChampionP) * currHaveChampionP;
            nonZeroP = nonZeroP * currNonZeroP;
        }
        printf("%.3f\n", haveChampionP);
    }
    return 0;
}

