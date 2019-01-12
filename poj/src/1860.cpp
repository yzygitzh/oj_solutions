/*
 * POJ 1860 - Currency Exchange
 *
 * Instead of calculating shortest path, we calculate
 * maximum amount of money remaining at each point
 *
 * Dynamic programming, use Bellman-Ford
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

using namespace std;

double rate[110][110] = {0};
double commission[110][110] = {0};
double maxMoney[110] = {0};
vector<pair<int, int> > edgeList;
int nodeNum, edgeNum, moneyType;
double initMoney;

double getMax(double a, double b) {
    return a > b ? a : b;
}

int main() {
    cin >> nodeNum >> edgeNum >> moneyType >> initMoney;
    for (int i = 0; i < edgeNum; i++) {
        int src, tgt;
        cin >> src >> tgt;
        cin >> rate[src][tgt] >> commission[src][tgt];
        cin >> rate[tgt][src] >> commission[tgt][src];
        edgeList.push_back(make_pair(src, tgt));
        edgeList.push_back(make_pair(tgt, src));
    }

    // Bellman-Ford, relax one more time
    maxMoney[moneyType] = initMoney;
    bool isYes = false;
    for (int i = 0; i < nodeNum; i++) {
        for (int j = 0; j < edgeNum * 2; j++) {
            int typeA = edgeList[j].first, typeB = edgeList[j].second;
            if (maxMoney[typeA] >= commission[typeA][typeB]) {
                double newMoney = (maxMoney[typeA] - commission[typeA][typeB]) * rate[typeA][typeB];
                if (newMoney > maxMoney[typeB]) {
                    maxMoney[typeB] = newMoney;
                    if (i + 1 == nodeNum) isYes = true;
                }
            }
        }
    }

    if (isYes) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
