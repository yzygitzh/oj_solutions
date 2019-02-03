/*
 * POJ 1062 - 昂贵的聘礼
 *
 * Find shortest path from "having none" to "having daughter".
 * Consider nodes within M from top leader only. Enumerate level ranges.
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <map>
#include <set>
#include <set>
#include <queue>

using namespace std;

int main() {
    // 0 is "have nothing"
    int M, N;
    int maxLvl = (1 << 31), minLvl = ~(1 << 31);

    cin >> M >> N;
    // src, <tgt, weight>
    vector<vector<pair<int, int> > > adjList(N + 1);
    vector<int> idToLvl(N + 1);
    int minCost;
    for (int i = 0; i < N; i++) {
        int P, L, X;
        cin >> P >> L >> X;
        if (i == 0) minCost = P;
        if (L < minLvl) minLvl = L;
        if (L > maxLvl) maxLvl = L;
        idToLvl[i + 1] = L;
        adjList[0].push_back(make_pair(i + 1, P));
        for (int j = 0; j < X; j++) {
            int T, V;
            cin >> T >> V;
            adjList[T].push_back(make_pair(i + 1, V));
        }
    }

    // enumerate level range
    for (int lvl = minLvl; lvl <= maxLvl; lvl++) {
        // <weight, target> in queue
        vector<int> minDis(N + 1, ~(1 << 31));
        minDis[0] = 0;
        vector<int> visited(N + 1, 0);
        priority_queue<pair<int, int>,
                       vector<pair<int, int> >,
                       greater<pair<int, int> > > edgeQ;
        edgeQ.push(make_pair(0, 0));
    
        while (!edgeQ.empty()) {
            pair<int, int> node = edgeQ.top();
            edgeQ.pop();
            if (visited[node.second]) continue;
            visited[node.second] = 1;
            for (vector<pair<int, int> >::iterator itr =
                 adjList[node.second].begin();
                 itr != adjList[node.second].end(); ++itr) {
                if (minDis[node.second] + itr->second < minDis[itr->first] &&
                    lvl <= idToLvl[itr->first] && idToLvl[itr->first] <= lvl + M) {
                    minDis[itr->first] = minDis[node.second] + itr->second;
                    edgeQ.push(make_pair(minDis[itr->first], itr->first));
                }
            }
        }
        if (minDis[1] < minCost) minCost = minDis[1];
    }
    cout << minCost << endl;
    return 0;
}
