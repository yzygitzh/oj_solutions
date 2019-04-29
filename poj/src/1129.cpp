/*
 * POJ 1129 - Channel Allocation
 *
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

int nodeNum;
int connCnt[30];
int connGraph[30][30];
int channelVisited[30][30];

bool dfs(int idx, int channelNum) {
    if (idx == nodeNum) return true;
    if (connCnt[idx] == 0) return dfs(idx + 1, channelNum);
    if (idx == 0) {
        // always choose channel 0 for node 0
        for (int i = idx + 1; i < nodeNum; i++) {
            if (connGraph[idx][i]) {
                channelVisited[i][0] = 1;
            }
        }
        return dfs(idx + 1, channelNum);
    } else {
        for (int i = 0; i < channelNum; i++) {
            if (!channelVisited[idx][i]) {
                for (int j = idx + 1; j < nodeNum; j++) {
                    if (connGraph[idx][j]) {
                        channelVisited[j][i] = 1;
                    }
                }
                if (dfs(idx + 1, channelNum)) return true;
                for (int j = idx + 1; j < nodeNum; j++) {
                    if (connGraph[idx][j]) {
                        channelVisited[j][i] = 0;
                    }
                }
            }
        }
        return false;
    }
}

int main() {
    string connInfo;
    while (true) {
        cin >> nodeNum;
        if (nodeNum == 0) break;
        memset(connGraph, 0, sizeof(connGraph));
        memset(connCnt, 0, sizeof(connCnt));
        for (int i = 0; i < nodeNum; i++) {
            cin >> connInfo;
            for (int j = 2; j < connInfo.length(); j++) {
                connCnt[connInfo[0] - 'A']++;
                connGraph[connInfo[0] - 'A'][connInfo[j] - 'A'] = 1;
            }
        }
        int left = 1, right = nodeNum;
        while (left + 1 < right) {
            int mid = left + (right - left) / 2;
            memset(channelVisited, 0, sizeof(channelVisited));
            if (dfs(0, mid)) right = mid;
            else left = mid;
        }
        int minChannelNum = dfs(0, left) ? left : right;
        cout << minChannelNum << " channel" << (minChannelNum > 1 ? "s" : "") << " needed." << endl;
    }
    return 0;
}

