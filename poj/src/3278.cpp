/*
 * POJ 3278 - Catch That Cow
 *
 * BFS since there are only ~100000 states
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

int N, K;
int visited[100010];

int bfs() {
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int> > bfsQ;
    bfsQ.push(make_pair(N, 0));
    visited[N] = 1;
    while (!bfsQ.empty()) {
        int n = bfsQ.front().first;
        int step = bfsQ.front().second;
        bfsQ.pop();
        if (n == K) return step;
        if (n + 1 <= 100000 && !visited[n + 1]) {
            visited[n + 1] = 1;
            bfsQ.push(make_pair(n + 1, step + 1));
        }
        if (n - 1 >= 0 && !visited[n - 1]) {
            visited[n - 1] = 1;
            bfsQ.push(make_pair(n - 1, step + 1));
        }
        if (n * 2 <= 100000 && !visited[n * 2]) {
            visited[n * 2] = 1;
            bfsQ.push(make_pair(n * 2, step + 1));
        }
    }
    return -1;
}

int main() {
    cin >> N >> K;
    int minStep = 0;
    cout << bfs() << endl;
    return 0;
}

