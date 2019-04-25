/*
 * POJ 3126 - Prime Path
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

int isPrime[10010];
int visited[10010];

void findPrimes() {
    for (int i = 0; i < 10010; i++) isPrime[i] = 1;
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= 10010; i++) {
        if (isPrime[i]) {
            for (int j = 2; i * j < 10010; j++) {
                isPrime[i * j] = 0;
            }
        }
    }
}

int bfs(int startPrime, int endPrime) {
    memset(visited, 0, sizeof(visited));
    queue<pair<int, int> > bfsQ;
    bfsQ.push(make_pair(startPrime, 0));
    visited[startPrime] = 1;
    while (!bfsQ.empty()) {
        int num = bfsQ.front().first;
        int steps = bfsQ.front().second;
        bfsQ.pop();
        if (num == endPrime) return steps;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 10; j++) {
                if (i == 3 && j == 0) continue; // no leading zero
                int loss = num, load = j;
                for (int k = 0; k < i; k++) loss /= 10;
                loss %= 10;
                for (int k = 0; k < i; k++) {
                    loss *= 10;
                    load *= 10;
                }
                int newNum = num - loss + load;
                if (!visited[newNum] && isPrime[newNum]) {
                    visited[newNum] = 1;
                    bfsQ.push(make_pair(newNum, steps + 1));
                }
            }
        }
    }
    return -1;
}

int main() {
    int caseNum;
    cin >> caseNum;
    findPrimes();
    for (int i = 0; i < caseNum; i++) {
        int startPrime, endPrime;
        cin >> startPrime >> endPrime;
        int steps = bfs(startPrime, endPrime);
        if (steps < 0) {
            cout << "Impossible" << endl;
        } else {
            cout << steps << endl;
        }
    }
    return 0;
}

