/*
 * POJ 3253 - Fence Repair
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

int main() {
    priority_queue<long long, vector<long long>, greater<long long> > huffmanTree;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        long long len;
        cin >> len;
        huffmanTree.push(len);
    }
    long long cost = 0;
    for (int i = 0; i < N - 1; i++) {
        int len1 = huffmanTree.top();
        huffmanTree.pop();
        int len2 = huffmanTree.top();
        huffmanTree.pop();
        huffmanTree.push(len1 + len2);
        cost += len1 + len2;
    }
    cout << cost << endl;
    return 0;
}

