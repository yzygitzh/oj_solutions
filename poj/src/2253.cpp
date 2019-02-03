/*
 * POJ 2253 - Frogger
 * 
 * Use minimax distance as Dijkstra's optimization target.
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

double G[210][210];
double stones[210][2];
double miniMaxJump[210];
int visited[210];
int stoneNum;

int main() {
    int caseNum = 0;
    while (true) {
        scanf("%d", &stoneNum);
        if (stoneNum == 0) break;
        for (int i = 0; i < stoneNum; i++) {
            scanf("%lf%lf", &stones[i][0], &stones[i][1]);
        }
        // calculate distances
        for (int i = 0; i < stoneNum; i++) {
            for (int j = i; j < stoneNum; j++) {
                G[i][j] = G[j][i] = sqrt(pow(stones[i][0] - stones[j][0], 2) +
                                         pow(stones[i][1] - stones[j][1], 2));
            }
        }
        for (int i = 0; i < stoneNum; i++) {
            miniMaxJump[i] = 1e9;
            visited[i] = 0;
        }
        miniMaxJump[0] = 0;
        // dijkstra
        for (int i = 0; i < stoneNum; i++) {
            // choose min point
            double minJump = 1e9;
            int minPoint;
            for (int j = 0; j < stoneNum; j++) {
                if (!visited[j] && miniMaxJump[j] < minJump) {
                    minJump = miniMaxJump[j];
                    minPoint = j;
                }
            }
            visited[minPoint] = 1;
            // check 0-minPoint -> minPoint-j and 0-j 
            for (int j = 0; j < stoneNum; j++) {
                miniMaxJump[j] = min(miniMaxJump[j], max(miniMaxJump[minPoint], G[minPoint][j]));
            }
        }
        caseNum++;
        printf("Scenario #%d\n", caseNum);
        printf("Frog Distance = %1.3f\n\n", miniMaxJump[1]);
    }
    return 0;
}
