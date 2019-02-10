/*
 * POJ 1837 - Balance
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

int C, G;
int F[30][16000] = {0};
int hooks[30];
int weights[30];

int main() {
    cin >> C >> G;
    for (int i = 0; i < C; i++) {
        cin >> hooks[i];
    }
    for (int i = 0; i < G; i++) {
        cin >> weights[i];
    }
    F[0][0 + 8000] = 1;
    for (int i = 1; i <= G; i++) {
        for (int j = 0; j < C; j++) {
            int weightedHook = hooks[j] * weights[i - 1];
            for (int k = 0; k < 16000; k++) {
                if (k - weightedHook >= 0 && k - weightedHook < 16000) {
                    F[i][k] += F[i - 1][k - weightedHook];
                }
            }
        }
    }
    cout << F[G][0 + 8000] << endl;
    return 0;
}

