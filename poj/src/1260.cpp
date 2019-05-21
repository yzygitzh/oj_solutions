/*
 * POJ 1260 - Pearls
 *
 * If we decide to buy one class's pearls, buying all we need is optimal,
 * or we can always replace higher pearls into lower ones to get a better
 * solution.
 *
 * minCost[M][2]: minimum cost to buy highest M classes if buying the M-th or not.
 * minCost[M][0] = min(minCost[m][1] + cost(m) * num_sum(m...M)), m < M
 * minCost[M][1] = min(minCost[M-1][0], minCost[M-1][1]) + cost(M) * (num(M) + 10)
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

int numC;
int price[110], acquire[110];
int minCost[110][2];

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        cin >> numC;
        for (int i = 0; i < numC; i++) {
            cin >> acquire[i + 1] >> price[i + 1];
        }
        memset(minCost, 0, sizeof(minCost));
        for (int i = 1; i <= numC; i++) {
            // we have to buy the royal class pearl, i.e. minCost[1][0] is invalid
            if (i > 1) {
                int pearlSum = acquire[numC - i + 1];
                minCost[i][0] = minCost[i - 1][1] +
                                price[numC - i + 2] * pearlSum;
                for (int j = i - 1; j > 1; j--) {
                    pearlSum += acquire[numC - j + 1];
                    minCost[i][0] = min(minCost[i][0], minCost[j - 1][1] +
                                    price[numC - j + 2] * pearlSum);
                }
            }
            minCost[i][1] = minCost[i - 1][1] +
                            price[numC - i + 1] * (acquire[numC - i + 1] + 10);
            // minCost[1][0] is invalid
            if (i != 2) {
                minCost[i][1] = min(minCost[i][1], minCost[i - 1][0] +
                                price[numC - i + 1] * (acquire[numC - i + 1] + 10));
            }
        }
        if (numC != 1) {
            cout << min(minCost[numC][0], minCost[numC][1]) << endl;
        } else {
            cout << minCost[numC][1] << endl;
        }
    }

    return 0;
}

