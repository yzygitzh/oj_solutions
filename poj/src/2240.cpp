/*
 * POJ 2240 - Arbitrage
 * 
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <queue>

using namespace std;

double G[35][35];

int main() {
    int caseNum = 0;
    while (true) {
        int cNum;
        cin >> cNum;
        if (cNum == 0) break;
        for (int i = 0; i < cNum; i++) {
            for (int j = 0; j < cNum; j++) {
                G[i][j] = 0.0;
            }
        }
        map<string, int> cToIdx;
        for (int i = 0; i < cNum; i++) {
            string cName;
            cin >> cName;
            cToIdx[cName] = i;
        }
        int edgeNum;
        cin >> edgeNum;
        for (int i = 0; i < edgeNum; i++) {
            string cName1, cName2;
            double rate;
            cin >> cName1 >> rate >> cName2;
            G[cToIdx[cName1]][cToIdx[cName2]] = rate;
        }
        // floyd
        for (int k = 0; k < cNum; k++) {
            for (int i = 0; i < cNum; i++) {
                for (int j = 0; j < cNum; j++) {
                    G[i][j] = max(G[i][j], G[i][k] * G[k][j]);
                }
            }
        }
        bool possible = false;
        for (int i = 0; i < cNum; i++) {
            if (G[i][i] > 1.0) {
                possible = true;
                break;
            }
        }
        caseNum++;
        cout << "Case " << caseNum << ": " << (possible ? "Yes" : "No") << endl;
    }
    return 0;
}
