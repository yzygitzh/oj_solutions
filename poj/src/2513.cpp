/*
 * POJ 2513 - Colored Sticks
 *
 * Eularian path
 * Need to judge non-connected graph
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
#include <unordered_map>
#include <cmath>

using namespace std;

int findParent(int idx, vector<int>& parent) {
    if (parent[idx] != idx) {
        parent[idx] = findParent(parent[idx], parent);
    }
    return parent[idx];
}

void unionSet(int idx1, int idx2, vector<int>& parent) {
    int parent1 = findParent(idx1, parent);
    int parent2 = findParent(idx2, parent);
    parent[parent1] = parent2;
}

bool isSplitGraph(vector<int>& parent) {
    for (auto p : parent) {
        if (findParent(p, parent) != findParent(0, parent)) return true;
    }
    return false;
}

int main() {
    char color1[20], color2[20];
    int currColorId = 0;
    unordered_map<string, int> colorId;
    unordered_map<int, int> stickCnt;
    vector<int> parent;

    while (true) {
        if (scanf("%s %s", color1, color2) <= 0) {
            break;
        }
        string color1Str(color1), color2Str(color2);
        if (!colorId.count(color1Str)) {
            colorId[color1Str] = currColorId;
            parent.push_back(currColorId++);
        }
        if (!colorId.count(color2Str)) {
            colorId[color2Str] = currColorId;
            parent.push_back(currColorId++);
        }
        stickCnt[colorId[color1Str]]++;
        stickCnt[colorId[color2Str]]++;
        unionSet(colorId[color1Str], colorId[color2Str], parent);
    }

    int oddCnt = 0;
    for (auto itr = stickCnt.begin(); itr != stickCnt.end(); ++itr) {
        if (itr->second % 2) {
            oddCnt++;
        }
    }

    if (oddCnt > 0 && oddCnt != 2 || isSplitGraph(parent)) {
        printf("Impossible\n");
    } else {
        printf("Possible\n");
    }

    return 0;
}

