/*
 * POJ 1094 - Sorting It All Out
 *
 * Maintain edges points, then do topo sort
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

int n, m;

pair<string, bool> topoSort(map<char, set<char> > edges,
                            map<char, int> degrees) {
    string result;
    queue<char> zeroQ;
    for (int i = 0; i < n; i++) {
        if (degrees.count('A' + i) &&
            degrees['A' + i] == 0) zeroQ.push('A' + i);
    }
    bool nonUnique = false;
    while (zeroQ.size() > 0) {
        if (zeroQ.size() != 1) nonUnique = true;
        char c = zeroQ.front();
        zeroQ.pop();
        result += c;
        for (set<char>::iterator itr = edges[c].begin();
             itr != edges[c].end(); ++itr) {
            degrees[*itr]--;
            if (degrees[*itr] == 0) {
                zeroQ.push(*itr);
            }
        }
        edges.erase(c);
    }
    return make_pair(result, !nonUnique);
}

int main() {
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;
        map<char, set<char> > edges;
        map<char, int> degrees;
        for (int i = 0; i < n; i++) {
            degrees['A' + i] = 0;
        }
        // for each relationship do topo sort
        int inconsistencyIdx = -1, successIdx = -1;
        string successResult;
        for (int i = 0; i < m; i++) {
            string rel;
            cin >> rel;
            if (!edges[rel[0]].count(rel[2])) {
                edges[rel[0]].insert(rel[2]);
                degrees[rel[2]]++;
                pair<string, bool> topoResult = topoSort(edges, degrees);
                if (topoResult.first.length() != n &&
                    inconsistencyIdx < 0 && successIdx < 0) {
                    inconsistencyIdx = i + 1;
                } else if (topoResult.first.length() == n && topoResult.second &&
                           successIdx < 0 && inconsistencyIdx < 0) {
                    successIdx = i + 1;
                    successResult = topoResult.first;
                }
            }
        }

        if (successIdx >= 0) {
            cout << "Sorted sequence determined after " << successIdx
                 << " relations: " << successResult << "." << endl;
        } else if (inconsistencyIdx >= 0) {
            cout << "Inconsistency found after " << inconsistencyIdx << " relations." << endl;
        } else {
            cout << "Sorted sequence cannot be determined." << endl;
        }
    }
    return 0;
}

