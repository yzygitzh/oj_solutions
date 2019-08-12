/*
 * POJ 3411 - Paid Roads
 *
 * This solution doesn't get accepted yet, but I cannot find any problem
 * by random checking with solutions get accepted
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

int N, M;
struct Road {
    int a, b, c, p, r;
    Road() {}
    Road(int _a, int _b, int _c, int _p, int _r)
        : a(_a), b(_b), c(_c), p(_p), r(_r) {}
};
// save road id
vector<Road> roads;
vector<vector<int> > graph;
vector<vector<int> > prepay;

// 10-bit(0-9) for pre-paid road, 10 slots for current city
int minCost[1024][10];

void dfs(int currCity, int currCost, int currPrepay) {
    if (minCost[currPrepay][currCity] > currCost) {
        minCost[currPrepay][currCity] = currCost;
        // try prepay
        for (int i = 0; i < prepay[currCity].size(); i++) {
            int roadId = prepay[currCity][i];
            Road road = roads[roadId];
            int newPrepay = currPrepay | (1 << roadId);
            if (currPrepay != newPrepay) {
                dfs(currCity, currCost + road.p, newPrepay);
            }
        }
        // try walk
        for (int i = 0; i < graph[currCity].size(); i++) {
            int roadId = graph[currCity][i];
            Road road = roads[roadId];
            bool roadPrepaid = currPrepay & (1 << roadId);
            int newPrepay = roadPrepaid ? currPrepay - (1 << roadId) : currPrepay;
            dfs(road.b, currCost + (roadPrepaid ? 0 : road.r), newPrepay);
        }
    }
}

int main() {
    scanf("%d%d", &N, &M);
    graph.reserve(N);
    prepay.reserve(N);
    for (int i = 0; i < M; i++) {
        int a, b, c, p, r;
        scanf("%d%d%d%d%d", &a, &b, &c, &p, &r);
        a--, b--, c--;
        roads.push_back(Road(a, b, c, p, r));
        graph[a].push_back(i);
        prepay[c].push_back(i);
    }
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 10; j++) {
            minCost[i][j] = 0x7FFFFFFF;
        }
    }
    dfs(0, 0, 0);
    int answer = 0x7FFFFFFF;
    for (int i = 0; i < (1 << M); i++) {
        answer = min(answer, minCost[i][N - 1]);
    }
    if (answer == 0x7FFFFFFF) {
        printf("impossible\n");
    } else {
        printf("%d\n", answer);
    }
    return 0;
}

