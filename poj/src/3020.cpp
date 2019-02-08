/*
 * POJ 3020 - Antenna Placement
 *
 * Build bi-partie graph, where positions are edges and antennas are nodes.
 * Find minimum edge coverage, i.e. n - maximum match.
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

int row, col;
char maze[50][20];
int nodes;
int stars;
vector<vector<int> > edges(2000);
vector<int> matched(2000);
vector<int> visited(2000);

int posToId(pair<int, int> pos) {
    return pos.first * col + pos.second;
}

bool dfs(int node) {
    for (vector<int>::iterator itr = edges[node].begin();
         itr != edges[node].end(); ++itr) {
        if (visited[*itr]) continue;
        visited[*itr] = 1;
        if (matched[*itr] == -1 || dfs(matched[*itr])) {
            matched[node] = *itr;
            matched[*itr] = node;
            return true;
        }
    }
    return false;
}

int hungarian() {
    int result = 0;
    for (int i = 0; i < nodes; i++) {
        for (int i = 0; i < nodes; i++) {
            visited[i] = visited[i + 1000] = 0;
        }
        if (matched[i] == -1 && dfs(i)) {
            result++;
        }
    }
    return result;
}

int main() {
    int caseNum;
    cin >> caseNum;
    while (caseNum--) {
        cin >> row >> col;
        nodes = row * col;
        stars = 0;
        for (int i = 0; i < nodes; i++) {
            edges[i].clear();
            edges[i + 1000].clear();
            matched[i] = matched[i + 1000] = -1;
        }
        for (int i = 0; i < row; i++) {
            string inputLine;
            cin >> inputLine;
            memcpy(maze[i], inputLine.c_str(), col);
            for (int j = 0; j < col; j++) {
                // see left and up
                if (maze[i][j] == '*') {
                    stars++;
                    if (j - 1 >= 0 && maze[i][j - 1] == '*') {
                        edges[posToId(make_pair(i, j))].push_back(posToId(make_pair(i, j - 1)) + 1000);
                        edges[posToId(make_pair(i, j - 1)) + 1000].push_back(posToId(make_pair(i, j)));
                        edges[posToId(make_pair(i, j)) + 1000].push_back(posToId(make_pair(i, j - 1)));
                        edges[posToId(make_pair(i, j - 1))].push_back(posToId(make_pair(i, j)) + 1000);
                    }
                    if (i - 1 >= 0 && maze[i - 1][j] == '*') {
                        edges[posToId(make_pair(i, j))].push_back(posToId(make_pair(i - 1, j)) + 1000);
                        edges[posToId(make_pair(i - 1, j)) + 1000].push_back(posToId(make_pair(i, j)));
                        edges[posToId(make_pair(i, j)) + 1000].push_back(posToId(make_pair(i - 1, j)));
                        edges[posToId(make_pair(i - 1, j))].push_back(posToId(make_pair(i, j)) + 1000);
                    }
                }
            }
        }
        cout << (2 * stars - hungarian()) / 2 << endl;
    }
    return 0;
}

