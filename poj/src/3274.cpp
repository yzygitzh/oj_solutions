/*
 * POJ 3274 - Gold Balanced Lineup
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

int N, K;
vector<int> featureCnt[100010];
map<vector<int>, pair<int, int> > featureHash;

int main() {
    featureCnt[0] = vector<int>(40, 0);
    scanf("%d%d", &N, &K);
    for (int i = 1; i <= N; i++) {
        featureCnt[i] = vector<int>(40, 0);
        int cow;
        scanf("%d", &cow);
        for (int j = 0; j < K; j++) {
            featureCnt[i][j] = featureCnt[i - 1][j];
            if (cow & (1 << j)) featureCnt[i][j] += 1;
        }
    }
    int maxLen = 0;
    featureHash[featureCnt[0]] = make_pair(0, 0);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j < K; j++) {
            featureCnt[i][j] -= featureCnt[i][0];
        }
        featureCnt[i][0] = 0;
        if (!featureHash.count(featureCnt[i])) {
            featureHash[featureCnt[i]] = make_pair(i, i);
        } else {
            pair<int, int>& p = featureHash[featureCnt[i]];
            p.second = i;
            maxLen = max(maxLen, p.second - p.first);
        }
    }
    printf("%d\n", maxLen);
    return 0;
}

