/*
 * POJ 1416 - Shredding Company
 *
 * Note that answers with prefix zero must be rejected.
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

int target, paper;
string targetStr, paperStr;

int bestVal, bestCnt;
vector<pair<int, string> > currCut, bestCut;

void dfs(int rest, int idx, int sum) {
    if (rest == 0) {
        if (sum <= target && sum >= bestVal) {
            if (sum > bestVal) {
                bestCut = currCut;
                bestCnt = 1;
            } else {
                bestCnt++;
            }
            bestVal = sum;
        }
    } else {
        int restLen = paperStr.length() - idx;
        for (int i = 1; i <= restLen; i++) {
            if (rest == 1 && i != restLen) continue;
            string cutStr = paperStr.substr(idx, i);
            int cutVal = stoi(cutStr);
            currCut.push_back(make_pair(cutVal, cutStr));
            dfs(rest - 1, idx + i, sum + cutVal);
            currCut.pop_back();
        }
    }
}

int main() {
    while (true) {
        // no prefix zero
        cin >> target >> paper;
        if (target == 0 && paper == 0) break;
        targetStr = to_string(target);
        paperStr = to_string(paper);
        bestVal = -1;
        bestCnt = 0;
        bestCut.clear();
        currCut.clear();
        if (target == paper) {
            cout << target << " " << paper << endl;
        } else {
            for (int i = 1; i <= paperStr.length(); i++) {
                dfs(i, 0, 0);
            }
            if (bestVal == -1) {
                cout << "error" << endl;
            } else if (bestCnt > 1) {
                cout << "rejected" << endl;
            } else {
                cout << bestVal;
                for (auto p : bestCut) {
                    cout << " " << p.second;
                }
                cout << endl;
            }
        }
    }
    return 0;
}

