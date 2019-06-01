/*
 * POJ 2635 - The Embarrassed Cryptographer
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

unsigned char visited[1000010];
vector<int> primes;

int main() {
    // calc prime list
    for (int i = 2; i <= 1000000; i++) {
        if (!visited[i]) {
            primes.push_back(i);
            for (int j = i; j <= 1000000; j += i) {
                visited[j] = 1;
            }
        }
    }
    while (true) {
        memset(visited, 0, sizeof(visited));
        string K, L;
        int LNum;
        cin >> K >> L;
        if (K == "0" && L == "0") {
            break;
        }
        LNum = atoi(L.c_str());
        int answer = 1;
        for (int i = 0; i < primes.size() && primes[i] < LNum; i++) {
            // divide operation
            int KSeg = 0;
            for (int j = 0; j < K.length(); j++) {
                KSeg *= 10;
                KSeg += K[j] - '0';
                KSeg %= primes[i];
            }
            if (KSeg == 0) {
                answer = primes[i];
                break;
            }
        }
        if (answer > 1) {
            cout << "BAD " << answer << endl;
        } else {
            cout << "GOOD" << endl;
        }
    }
    return 0;
}

