/*
 * POJ 1426 - Find The Multiple
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

int N;
int visited[210];

string bfs() {
    memset(visited, 0, sizeof(visited));
    // digits, remainder
    queue<pair<string, int> > bfsQ;
    bfsQ.push(make_pair("1", 1 % N));
    visited[1 % N] = 1;
    while (!bfsQ.empty()) {
        string digits = bfsQ.front().first;
        int remainder = bfsQ.front().second;
        bfsQ.pop();
        if (remainder == 0) return digits;
        if (!visited[(remainder * 10) % N]) {
            visited[(remainder * 10) % N] = 1;
            string newDigits = digits;
            newDigits += '0';
            bfsQ.push(make_pair(newDigits, (remainder * 10) % N));
        }
        if (!visited[(remainder * 10 + 1) % N]) {
            visited[(remainder * 10 + 1) % N] = 1;
            string newDigits = digits;
            newDigits += '1';
            bfsQ.push(make_pair(newDigits, (remainder * 10 + 1) % N));
        }
    }
    return "0";
}

int main() {
    while (true) {
        cin >> N;
        if (N == 0) break;
        cout << bfs() << endl;
    }
    return 0;
}

