/*
 * POJ 1845 - Sumdiv
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

vector<pair<int, int> > factors;

void findFactors(int a) {
    for (int i = 2; i * i <= a; i++) {
        int count = 0;
        while (!(a % i)) {
            count++;
            a /= i;
        }
        if (count) {
            factors.push_back(make_pair(i, count));
        }
    }
    if (a > 1) {
        factors.push_back(make_pair(a, 1));
    }
}

// a > 1
int calcPowMod(int a, int b, int n) {
    if (b == 0) {
        return 1;
    } if (b == 1) {
        return a % n;
    } else {
        int half = calcPowMod(a, b / 2, n);
        half = (half * half) % n;
        if (b % 2) {
            half = (half * (a % n)) % n;
        }
        return half;
    }
}

// a > 1
// find (1 + a^1 + ... + a^b) % n
int calcPowSeries(int a, int b, int n) {
    if (b == 0) {
        return 1;
    } else if (b == 1) {
        return (a + 1) % n;
    } else {
        int half = calcPowSeries(a, (b - 1) / 2, n);
        int halfPow = calcPowMod(a, (b + 1) / 2, n) % n;
        if (b % 2) {
            // 1 + a + a^2 + a^3 == (1 + a)(a^2)
            return (half + half * halfPow) % n;
        } else {
            // 1 + a + a^2 == (1)(a) + a^2
            // 1 + a + a^2 + a^3 + a^4 == (1 + a)(a^2) + a^4
            int fullPow = calcPowMod(a, b, n) % n;
            return (half + half * halfPow + fullPow) % n;
        }
    }
}

int findAns(int a, int b, int n) {
    findFactors(a);
    int ans = 1;
    for (int i = 0; i < factors.size(); i++) {
        int base = factors[i].first;
        int power = factors[i].second * b;
        ans = (ans * calcPowSeries(base, power, n)) % n;
    }
    return ans;
}

int main() {
    int a, b;
    cin >> a >> b;
    if (a == 1 || b == 0) {
        cout << 1 << endl;
    } else if (a == 0) {
        cout << 0 << endl;
    } else {
        // a > 1 and b > 0
        cout << findAns(a, b, 9901) << endl;
    }
    return 0;
}

