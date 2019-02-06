/*
 * POJ 3041 - Asteroids
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
vector<set<int> > adjList(2000);
vector<int> visited(2000, 0);
vector<int> matched(2000, -1);

bool dfs(int node) {
    for (set<int>::iterator itr = adjList[node].begin();
         itr != adjList[node].end(); ++itr) {
        if (visited[*itr]) continue;
        visited[*itr] = 1;
        if (matched[*itr] == -1 || dfs(matched[*itr])) {
            matched[*itr] = node;
            matched[node] = *itr;
            return true;
        }
    }
    return false;
}

int hungarian() {
    int maxMatch = 0;
    for (int i = 1; i <= N; i++) {
        if (matched[i] == -1) {
            for (int j = 1; j <= N; j++) {
                visited[j] = visited[j + 1000] = 0;
            }
            if (dfs(i)) maxMatch++;
        }
    }
    return maxMatch;
}

int main() {
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        int src, tgt;
        cin >> src >> tgt;
        adjList[src].insert(tgt + 1000);
        adjList[tgt + 1000].insert(src);
    }
    cout << hungarian() << endl;
    return 0;
}

